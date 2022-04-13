
# include "Behaviors.hh"
# include "DirectedPath.hh"
# include "ForceBased.hh"

namespace mas {
  namespace environment {

    Swarm::Swarm():
      Behavior()
    {}

    bool
    Swarm::completed() const noexcept {
      // This behavior is never finished.
      return false;
    }

    std::vector<InfluenceShPtr>
    Swarm::perform(const AgentData& data,
                   const Perceptions& perceptions,
                   const time::Manager& /*manager*/)
    {
      // Scan perceptions and move towards the center of gravity
      // of the perceived objects.
      float cX = data.area.x();
      float cY = data.area.y();
      unsigned count = 1u;

      for (unsigned id = 0u ; id < perceptions.size() ; ++id) {
        cX += perceptions[id].bbox().x();
        cY += perceptions[id].bbox().y();

        ++count;
      }

      // Compute the average position to reach and generate
      // the influence corresponding to that. We combine a
      // motion to the target and a force based repulsion.
      DirectedPath dp;
      dp.target = utils::Vector2f(cX / count, cY / count);
      dp.arrivalRadius = 0.01f;
      dp.maxAcceleration = 1.0f;

      utils::Vector2f f1 = dp.motionToTarget(data.area.x(), data.area.y());

      ForceBased fb;
      fb.repulsion = 0.2f;
      fb.maxAcceleration = 2.0f;
      utils::Vector2f f2 = fb.computeAvoidanceVector(data.area.getCenter(), perceptions);

      InfluenceShPtr inf = std::make_shared<Influence>(
        influence::noOpEmitter(),
        [f1, f2](MovingObject& obj) {
          obj.applyForce(f1 + f2);
        }
      );

      return std::vector<InfluenceShPtr>(1u, inf);
    }

  }
}
