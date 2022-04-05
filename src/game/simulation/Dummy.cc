
# include "Dummy.hh"
# include "Impulse.hh"

namespace mas {
  namespace environment {

    AgentShPtr
    createDummy(Animat& animat) {
      // Generate callbacks.
      brain::BehaviorUpdate bu = [](const AgentData& d) {
        // Update the behavior is the agent is not moving
        // anymore.
        return !d.moving();
      };

      brain::BehaviorSelection bs = [](const AgentData& /*d*/, const Perceptions& /*perceptions*/, utils::RNG& rng) {
        float m = rng.rndFloat(0.0f, 20.0f);
        float a = rng.rndAngle();

        utils::Vector2f v(m * std::cos(a), m * std::sin(a));

        return std::make_shared<ImpulseBehavior>(v, false);
      };

      brain::BehaviorTermination bt = [](BehaviorShPtr b) {
        // Reset the pointer.
        b.reset();
        return b;
      };

      // Create the agent and plug it to the animat.
      AgentShPtr out = std::make_shared<Agent>(animat, bu, bs, bt);
      animat.plug(out.get());

      return out;
    }

  }
}
