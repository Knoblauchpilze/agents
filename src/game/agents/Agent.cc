
# include "Agent.hh"
# include "Animat.hh"
# include "Behavior.hh"

namespace mas {
  namespace environment {

    Agent::Agent(Animat& animat):
      utils::CoreObject("agent"),

      m_animat(animat),
      m_behavior(nullptr)
    {
      setService("mas");
    }

    void
    Agent::live() {
      // Check whether some behaviours are available.
      if (m_behavior == nullptr) {
        think();
      }

      if (m_behavior == nullptr) {
        return;
      }

      std::vector<InfluenceShPtr> infs = m_behavior->perform(m_animat.perceptions());
      for (unsigned id = 0u ; id < infs.size() ; ++id) {
        m_animat.influence(infs[id]);
      }

      if (m_behavior->completed()) {
        m_behavior.reset();
      }
    }

    void
    Agent::think() {
      /// TODO: Create a new behavior.
    }

  }
}
