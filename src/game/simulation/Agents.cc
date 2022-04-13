
# include "Agents.hh"
# include "Behaviors.hh"

namespace mas {
  namespace environment {

    AgentShPtr
    spawnFish(Animat& animat) {
      // Generate callbacks.
      brain::BehaviorUpdate bu = [](const AgentData& d) {
        // Update the behavior is the agent is not moving
        // anymore.
        return !d.moving();
      };

      brain::BehaviorSelection bs = [](const AgentData& /*d*/, const Perceptions& /*perceptions*/, utils::RNG& /*rng*/) {
        return std::make_shared<Swarm>();
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
