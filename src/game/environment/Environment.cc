
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
  iterate(const std::vector<mas::environment::EntityShPtr>& entities,
          const mas::environment::Type& t,
          std::function<void(mas::environment::Component&)> func) noexcept
  {
    for (unsigned id = 0u ; id < entities.size() ; ++id) {
      const mas::environment::Entity& e = *entities[id];

      for (eiterator it = e.begin() ; it != e.end() ; ++it) {
        if (it->type() != t) {
          continue;
        }

        func(*it);
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
    log("Stepping simulation for " + std::to_string(manager.lastStepDuration(time::Unit::Second)) + "second(s)");

    computePreAgentsStep(manager);
    computeAgentsStep(manager);
    computePostAgentsStep(manager);
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
  }

}
