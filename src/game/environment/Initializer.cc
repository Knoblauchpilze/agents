
# include "Initializer.hh"
# include <core_utils/RNG.hh>
# include "Environment.hh"
# include "Animat.hh"
# include "Renderer.hh"
# include "Dummy.hh"

/// @brief - How many objects are spawned at the beginning.
# define AGENTS_COUNT 5u

namespace mas {
 namespace environment {

    Initializer::Initializer(const utils::Boxf& area):
      utils::CoreObject("initializer"),

      m_area(area)
    {
      setService("mas");
    }

    void
    Initializer::operator()(Environment& env) {
      // Create a RNG.
      utils::RNG rng = utils::RNG::createRandomRNG();

      log("Generating elements within " + m_area.toString(), utils::Level::Info);

      unsigned id = 0u;
      while (id < AGENTS_COUNT) {
        // Pick a position.
        float x = rng.rndFloat(m_area.getLeftBound(), m_area.getRightBound());
        float y = rng.rndFloat(m_area.getBottomBound(), m_area.getTopBound());

        utils::Uuid uuid = env.createEntity();

        log("Spawning agent at " + std::to_string(x) + "x" + std::to_string(y));

        // An agent should be assigned a moving object, an
        // animat, its brain, and a renderer.
        utils::Boxf area(x, y, 1.0f, 1.0f);
        RigidBody rb(1.0f, 1.0f, area);

        ComponentShPtr mo = std::make_shared<MovingObject>(area, rb);
        env.registerComponent(uuid, mo);

        ComponentShPtr ani = std::make_shared<Animat>(mo->as<MovingObject>());
        env.registerComponent(uuid, ani);

        ComponentShPtr ag = createDummy(*ani->as<Animat>());
        env.registerComponent(uuid, ag);

        ComponentShPtr rend = std::make_shared<Renderer>(*mo->as<MovingObject>(), RenderingMode::Square);
        env.registerComponent(uuid, rend);

        ++id;
      }
    }

 }
}
