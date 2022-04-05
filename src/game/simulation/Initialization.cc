
# include "Initialization.hh"
# include "Component.hh"
# include "Environment.hh"
# include "Renderer.hh"
# include "Dummy.hh"

/// @brief - The desired number of FPS for the launcher that
/// will simulate the environment.
# define DESIRED_FPS 10.0f

/// @brief - The decrease in speed due to friction and other
/// processing at each frame. This value is expressed in m/s2.
/// This correspond to an acceleration.
# define FRICTION_ACCELERATION 0.9f

/// @brief - The threshold indicating whether the agent is
/// still moving or not.
# define MOTION_SPEED_THRESHOLD 0.1f

/// @brief - How many objects are spawned at the beginning.
# define AGENTS_COUNT 1u

namespace {

}

namespace mas {
  namespace environment {

    Launcher
    createLauncher(Environment& env) noexcept {
      return Launcher(
        &env,
        DESIRED_FPS,
        1000.0f / DESIRED_FPS,
        mas::time::Unit::Millisecond
      );
    }

    void
    initialize(Environment& env) noexcept {
      // Create the spawner function.
      utils::Boxf area(0.0f, 0.0f, 10.0f, 5.0f);

      auto spawner = [area](utils::RNG& rng) {
        utils::Point2f p;
        p.x() = rng.rndFloat(area.getLeftBound(), area.getRightBound());
        p.y() = rng.rndFloat(area.getBottomBound(), area.getTopBound());

        return p;
      };

      // Create the entity factory function.
      auto factory = [](const utils::Uuid& uuid, const utils::Point2f& p, utils::RNG& /*rng*/, Environment& env) {
        // An agent should be assigned a moving object, an
        // animat, its brain, and a renderer.
        utils::Boxf area(p.x(), p.y(), 1.0f, 1.0f);
        RigidBody rb(1.0f, 1.0f, FRICTION_ACCELERATION, area);

        ComponentShPtr mo = std::make_shared<MovingObject>(area, rb);
        env.registerComponent(uuid, mo);

        ComponentShPtr ani = std::make_shared<Animat>(mo->as<MovingObject>(), MOTION_SPEED_THRESHOLD);
        env.registerComponent(uuid, ani);

        ComponentShPtr ag = createDummy(*ani->as<Animat>());
        env.registerComponent(uuid, ag);

        ComponentShPtr rend = std::make_shared<Renderer>(*mo->as<MovingObject>(), RenderingMode::Square);
        env.registerComponent(uuid, rend);
      };

      // Generate the initializer.
      Initializer init(AGENTS_COUNT, spawner, factory);
      init.setup(env);
    }

  }
}
