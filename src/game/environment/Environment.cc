
# include "Environment.hh"
# include "Influence.hh"
# include "Perception.hh"
# include "Frustum.hh"
# include "Animat.hh"
# include "MovingObject.hh"

/// @brief - Convenience define to reference an iterator
/// on the components of an entity.
using eiterator = mas::environment::Entity::iterator;

namespace {

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
          std::function<void(mas::environment::Component&)> func) noexcept
  {
    for (std::unordered_map<utils::Uuid, mas::environment::EntityShPtr>::const_iterator it = entities.cbegin() ; it != entities.cend() ; ++it) {
      const mas::environment::Entity& e = *it->second;

      for (eiterator eit = e.begin() ; eit != e.end() ; ++eit) {
        if (eit->type() != t) {
          continue;
        }

        func(*eit);
      }
    }
  }

}

namespace mas {

  Environment::Environment():
    utils::CoreObject("environment"),

    m_entities(),
    m_physic()
  {
    setService("mas");
  }

  Environment::~Environment() {}

  void
  Environment::simulate(const time::Manager& manager) {
    log("Stepping simulation for " + std::to_string(static_cast<int>(manager.lastStepDuration(time::Unit::Second))) + " second(s)");

    computePreAgentsStep(manager);
    computeAgentsStep(manager);
    computePostAgentsStep(manager);
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
    /// TODO: Register component in physic engine in case it is
    /// a moving object.

    it->second->add(comp);
  }

  void
  Environment::computePreAgentsStep(const time::Manager& /*manager*/) {
    // Traverse the list of entities and check ones that have
    // an animat component.
    iterate(m_entities, environment::Type::Animat,
      [this](environment::Component& c) {
        const environment::Frustum& frustum = c.as<environment::Animat>()->frustum();

        environment::Perceptions pps;

        iterate(m_entities, environment::Type::MovingObject,
          [&pps, &frustum](environment::Component& c) {
            environment::MovingObject* obj = c.as<environment::MovingObject>();
            if (obj != nullptr && frustum.visible(*obj)) {
              pps.push_back(environment::Perception(*obj));
            }
          }
        );

        c.as<environment::Animat>()->perceive(pps);
      }
    );
  }

  void
  Environment::computeAgentsStep(const time::Manager& /*manager*/) {
    iterate(m_entities, environment::Type::Agent,
      [](environment::Component& c) {
        c.as<environment::Agent>()->live();
      }
    );
  }

  void
  Environment::computePostAgentsStep(const time::Manager& manager) {
    // Collect influences.
    std::vector<environment::InfluenceShPtr> infs;

    iterate(m_entities, environment::Type::Animat,
      [&infs](environment::Component& c) {
        std::vector<environment::InfluenceShPtr> bInfs = c.as<environment::Animat>()->consumeInfluences();
        infs.insert(infs.end(), bInfs.begin(), bInfs.end());
      }
    );

    // Make the simulation move forward in time.
    m_physic.simulate(manager);

    // Apply influences.
    for (unsigned id = 0u ; id < infs.size() ; ++id) {
      infs[id]->apply();
    }

    // Apply endogenous processes.
    iterate(m_entities, environment::Type::MovingObject,
      [&manager](environment::Component& c) {
        c.as<environment::MovingObject>()->simulate(manager);
      }
    );

    // Update all entities and their components.
    for (Entities::iterator it = m_entities.begin() ; it != m_entities.end() ; ++it) {
      it->second->update();
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
