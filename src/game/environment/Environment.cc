
# include "Environment.hh"
# include "Influence.hh"
# include "Perception.hh"
# include "Frustum.hh"

namespace mas {

  Environment::Environment():
    utils::CoreObject("environment"),

    m_entities(),
    m_objects(),
    m_agents(),
    m_animats(),

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
    // Compute perceptions for each animat.
    for (unsigned id = 0u ; id < m_animats.size() ; ++id) {
      const environment::Frustum& frustum = m_animats[id]->frustum();

      // Traverse the list of objects and check for intersections.
      environment::Perceptions pps;
      for (unsigned id = 0u ; id < m_objects.size() ; ++id) {
        const environment::MovingObjectShPtr& obj = m_objects[id];
        if (obj != nullptr && frustum.visible(*obj)) {
          pps.push_back(environment::Perception(*obj));
        }
      }

      m_animats[id]->perceive(pps);
    }
  }

  void
  Environment::computeAgentsStep(const time::Manager& /*manager*/) {
    for (unsigned id = 0u ; id < m_agents.size() ; ++id) {
      m_agents[id]->live();
    }
  }

  void
  Environment::computePostAgentsStep(const time::Manager& manager) {
    // Collect influences.
    std::vector<environment::InfluenceShPtr> infs;

    for (unsigned id = 0u ; id < m_animats.size() ; ++id) {
      std::vector<environment::InfluenceShPtr> bInfs = m_animats[id]->consumeInfluences();
      infs.insert(infs.end(), bInfs.begin(), bInfs.end());
    }

    // Make the simulation move forward in time.
    m_physic.simulate(manager);

    // Apply influences.
    for (unsigned id = 0u ; id < infs.size() ; ++id) {
      infs[id]->apply();
    }

    // Apply endogenous processes.
    for (unsigned id = 0u ; id < m_objects.size() ; ++id) {
      m_objects[id]->simulate(manager);
    }
  }

}
