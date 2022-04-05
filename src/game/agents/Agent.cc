
# include "Agent.hh"
# include "Animat.hh"
# include "Behavior.hh"
# include "Impulse.hh"

namespace mas {
  namespace environment {

    Agent::Agent(Animat& animat,
                 brain::BehaviorUpdate bUpdate,
                 brain::BehaviorSelection bSelection,
                 brain::BehaviorTermination bTermination):
      Component(Type::Agent),

      m_animat(animat),
      m_behavior(nullptr),

      m_bUpdate(bUpdate),
      m_bSelection(bSelection),
      m_bTermination(bTermination)
    {
      setService("mas");
    }

    void
    Agent::update() {}

    void
    Agent::live(const time::Manager& manager,
                utils::RNG& rng)
    {
      AgentData d = m_animat.data();

      // Check whether some behaviors are available.
      if (m_behavior == nullptr && m_bUpdate(d)) {
        log("Agent is thinking very hard...", utils::Level::Verbose);
        m_behavior = m_bSelection(d, m_animat.perceptions(), rng);
      }

      if (m_behavior == nullptr) {
        return;
      }

      std::vector<InfluenceShPtr> infs = m_behavior->perform(d, m_animat.perceptions(), manager);
      for (unsigned id = 0u ; id < infs.size() ; ++id) {
        m_animat.influence(infs[id]);
      }

      if (m_behavior->completed()) {
        m_behavior = m_bTermination(m_behavior);
      }
    }

  }
}
