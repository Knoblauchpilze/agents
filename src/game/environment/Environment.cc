
# include "Environment.hh"
# include "Influence.hh"
# include "Perception.hh"
# include "Frustum.hh"
# include "Animat.hh"
# include "MovingObject.hh"

/// @brief - Convenience define to reference an iterator
/// on the components of an entity.
using eiterator = mas::environment::Entity::iterator;

namespace details {

  /**
   * @brief- Convenience function to iterate on a set of entities
   *         and only process components of each entity that match
   *         a type.
   * @param entities - the list of entities.
   * @param t - the type of the component to filter.
   * @param func - the process to apply to each matching component.
   */
  void
  iterate(const std::unordered_map<utils::Uuid, mas::environment::EntityShPtr>& entities,
          const mas::environment::Type& t,
          std::function<void(mas::environment::Component&, const mas::environment::Entity&)> func) noexcept
  {
    for (std::unordered_map<utils::Uuid, mas::environment::EntityShPtr>::const_iterator it = entities.cbegin() ; it != entities.cend() ; ++it) {
      const mas::environment::Entity& e = *it->second;

      for (eiterator eit = e.begin() ; eit != e.end() ; ++eit) {
        if (eit->type() != t) {
          continue;
        }

        func(*eit, e);
      }
    }
  }

  /**
   * @brief- Convenience function to iterate on a set of entities
   *         and process all of their components.
   * @param entities - the list of entities.
   * @param func - the process to apply to each component.
   */
  void
  iterateAll(const std::unordered_map<utils::Uuid, mas::environment::EntityShPtr>& entities,
             std::function<void(mas::environment::Component&)> func) noexcept
  {
    for (std::unordered_map<utils::Uuid, mas::environment::EntityShPtr>::const_iterator it = entities.cbegin() ; it != entities.cend() ; ++it) {
      const mas::environment::Entity& e = *it->second;

      for (eiterator eit = e.begin() ; eit != e.end() ; ++eit) {
        func(*eit);
      }
    }
  }

}

namespace mas {

  Environment::Environment():
    utils::CoreObject("environment"),

    m_rng(),

    m_entities(),
    m_physic()
  {
    setService("mas");
  }

  Environment::~Environment() {}

  utils::RNG&
  Environment::rng() noexcept {
    return m_rng;
  }

  void
  Environment::simulate(const time::Manager& manager) {
# ifdef LOG_STEP
    log(
      "Stepping simulation for " +
      std::to_string(static_cast<int>(manager.lastStepDuration(time::Unit::Millisecond))) +
      " millisecond(s)" +
      " (elapsed: " + std::to_string(static_cast<int>(manager.elapsed(time::Unit::Millisecond))) +
      " millisecond(s))",
      utils::Level::Verbose
    );
# endif

    computePreAgentsStep(manager);
    computeAgentsStep(manager);
    computePostAgentsStep(manager);
  }

  unsigned
  Environment::agents() const noexcept {
    Entities::const_iterator it = m_entities.cbegin();
    unsigned count = 0u;

    while (it != m_entities.cend()) {
      if (it->second->hasComponent(environment::Type::Agent)) {
        ++count;
      }

      ++it;
    }

    return count;
  }

  utils::Uuid
  Environment::createEntity() noexcept {
    environment::EntityShPtr ent = std::make_shared<environment::Entity>();
    m_entities[ent->uuid()] = ent;

    return ent->uuid();
  }

  void
  Environment::registerComponent(const utils::Uuid& ent, environment::ComponentShPtr comp) {
    Entities::iterator it = m_entities.find(ent);
    if (it == m_entities.end()) {
      warn(
        "Failed to register component for " + ent.toString(),
        "No such entity"
      );

      return;
    }

    // Register the object in the physic engine if needed.
    if (comp->type() == environment::Type::MovingObject) {
      m_physic.registerObject(comp->as<environment::MovingObject>());
    }

    it->second->add(comp);
  }

  void
  Environment::computePreAgentsStep(const time::Manager& /*manager*/) {
    // Traverse the list of entities and check ones that have
    // an animat component.
    details::iterate(m_entities, environment::Type::Animat,
      [this](environment::Component& c, const environment::Entity& /*e*/) {
        // Convert to animat.
        environment::Animat* a = c.as<environment::Animat>();

        // Compute perceptions.
        const environment::Frustum& frustum = a->frustum();
        environment::Perceptions pps;

        details::iterate(m_entities, environment::Type::MovingObject,
          [a, &pps, &frustum](environment::Component& c, const environment::Entity& e) {
            environment::MovingObject* obj = c.as<environment::MovingObject>();
            if (obj != nullptr && !a->isBody(obj) && frustum.visible(*obj)) {
              // Build a perception with the corresponding user data.
              environment::ComponentShPtr ud = e.get(environment::Type::UserData);

              environment::Perception p(*obj, ud == nullptr ? nullptr : ud->as<environment::UserData>());
              pps.push_back(p);
            }
          }
        );

        c.as<environment::Animat>()->perceive(pps);
      }
    );
  }

  void
  Environment::computeAgentsStep(const time::Manager& manager) {
    details::iterate(m_entities, environment::Type::Agent,
      [&manager, this](environment::Component& c, const environment::Entity& /*e*/) {
        c.as<environment::Agent>()->live(manager, m_rng);
      }
    );
  }

  void
  Environment::computePostAgentsStep(const time::Manager& manager) {
    // Collect influences.
    std::vector<environment::InfluenceShPtr> infs;

    details::iterate(m_entities, environment::Type::Animat,
      [&infs](environment::Component& c, const environment::Entity& /*e*/) {
        std::vector<environment::InfluenceShPtr> bInfs = c.as<environment::Animat>()->consumeInfluences();
        infs.insert(infs.end(), bInfs.begin(), bInfs.end());
      }
    );

    // Make the simulation move forward in time.
    m_physic.simulate(manager);

    // Apply influences.
    for (unsigned id = 0u ; id < infs.size() ; ++id) {
      infs[id]->apply(*this);
    }

    // Apply endogenous processes by updating entities and
    // their components.
    for (Entities::iterator it = m_entities.begin() ; it != m_entities.end() ; ++it) {
      it->second->simulate(manager);
    }

    // Delete entities with no components.
    std::size_t s = m_entities.size();
    Entities::iterator it = m_entities.begin();
    Entities::iterator eit = m_entities.end();
    while (it != eit) {
      if (it->second->components() == 0u) {
        log("Erasing entity " + it->second->uuid().toString(), utils::Level::Verbose);
        it = m_entities.erase(it);
      }
      else {
        ++it;
      }
    }

    if (m_entities.size() != s) {
      log("Removed " + std::to_string(s - m_entities.size()) + " empty entity(ies)");
    }
  }

  Environment::const_iterator
  Environment::cbegin() const noexcept {
    return const_iterator(m_entities.cbegin());
  }

  Environment::const_iterator
  Environment::cend() const noexcept {
    return const_iterator(m_entities.cend());
  }

  Environment::const_iterator::const_iterator(Entities::const_iterator it) noexcept:
    m_current(it)
  {}

  bool
  Environment::const_iterator::operator==(const const_iterator& rhs) const noexcept {
    return m_current == rhs.m_current;
  }

  bool
  Environment::const_iterator::operator!=(const const_iterator& rhs) const noexcept {
    return !operator==(rhs);
  }

  const environment::Entity&
  Environment::const_iterator::operator*() const noexcept {
    return *m_current->second;
  }

  environment::EntityShPtr
  Environment::const_iterator::operator->() const noexcept {
    return m_current->second;
  }

  Environment::const_iterator&
  Environment::const_iterator::operator++() noexcept {
    ++m_current;
    return *this;
  }

  Environment::const_iterator
  Environment::const_iterator::operator++(int) noexcept {
    return const_iterator(m_current++);
  }

}
