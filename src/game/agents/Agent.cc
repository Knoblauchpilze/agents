
# include "Agent.hh"
# include "Animat.hh"
# include "Behavior.hh"
# include "Impulse.hh"

namespace mas {
  namespace environment {

    Agent::Agent(Animat& animat):
      Component(Type::Agent),

      m_animat(animat),
      m_behavior(nullptr)
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
      if (m_behavior == nullptr && !d.moving()) {
        think(rng);
      }

      if (m_behavior == nullptr) {
        return;
      }

      std::vector<InfluenceShPtr> infs = m_behavior->perform(d, m_animat.perceptions(), manager);
      for (unsigned id = 0u ; id < infs.size() ; ++id) {
        m_animat.influence(infs[id]);
      }

      if (m_behavior->completed()) {
        m_behavior.reset();
      }
    }

    void
    Agent::think(utils::RNG& rng) {
      /// TODO: Create a new behavior.
      log("Agent is thinking very hard...", utils::Level::Verbose);

      float m = rng.rndFloat(0.0f, 20.0f);
      float a = rng.rndAngle();

      utils::Vector2f v(m * std::cos(a), m * std::sin(a));

      m_behavior = std::make_shared<ImpulseBehavior>(v, false);
    }

  }
}
