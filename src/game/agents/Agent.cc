
# include "Agent.hh"
# include "Animat.hh"
# include "Behavior.hh"

namespace mas {
  namespace environment {

    Agent::Agent(Animat& animat,
                 brain::BehaviorUpdate bUpdate,
                 brain::BehaviorSelection bSelection,
                 brain::BehaviorTermination bTermination):
      Component(Type::Agent),

      m_animat(animat),
      m_behaviors(),

      m_bUpdate(bUpdate),
      m_bSelection(bSelection),
      m_bTermination(bTermination)
    {
      setService("mas");
    }

    void
    Agent::simulate(const time::Manager& /*manager*/) {}

    void
    Agent::live(const time::Manager& manager,
                utils::RNG& rng)
    {
      AgentData d = m_animat.data();

      // Check whether some behaviors are available.
      if (m_behaviors.empty() && m_bUpdate(d)) {
        log("Agent is thinking very hard...", utils::Level::Verbose);
        BehaviorShPtr b = m_bSelection(d, m_animat.perceptions(), rng);
        if (b == nullptr) {
          warn("Behavior selection created empty behavior");
        }
        else {
          m_behaviors.push_back(b);
        }
      }

      if (m_behaviors.empty()) {
        return;
      }

      // Collect influences for all behaviors.
      std::vector<InfluenceShPtr> infs;
      for (unsigned id = 0u ; id < m_behaviors.size() ; ++id) {
        std::vector<InfluenceShPtr> is = m_behaviors[id]->perform(d, m_animat.perceptions(), manager);
        infs.insert(infs.end(), is.begin(), is.end());
      }

      // Propagate influences.
      for (unsigned id = 0u ; id < infs.size() ; ++id) {
        m_animat.influence(infs[id]);
      }

      // Update each behavior.
      for (unsigned id = 0u ; id < m_behaviors.size() ; ++id) {
        if (m_behaviors[id]->completed()) {
          m_behaviors[id] = m_bTermination(m_behaviors[id]);
        }
      }

      Behaviors::iterator it = std::remove_if(m_behaviors.begin(), m_behaviors.end(),
        [](BehaviorShPtr b) {
          return b == nullptr;
        }
      );
      m_behaviors.erase(it, m_behaviors.end());
    }

  }
}
