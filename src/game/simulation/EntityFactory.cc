
# include "EntityFactory.hh"
# include "Component.hh"
# include "Environment.hh"
# include "Renderer.hh"
# include "Dummy.hh"

namespace mas {
  namespace environment {

    EntityFactory
    createFactory() {
      return [](const utils::Uuid& uuid, const utils::Point2f& p, utils::RNG& /*rng*/, Environment& env) {
        // An agent should be assigned a moving object, an
        // animat, its brain, and a renderer.
        utils::Boxf area(p.x(), p.y(), 1.0f, 1.0f);
        RigidBody rb(1.0f, 1.0f, area);

        ComponentShPtr mo = std::make_shared<MovingObject>(area, rb);
        env.registerComponent(uuid, mo);

        ComponentShPtr ani = std::make_shared<Animat>(mo->as<MovingObject>());
        env.registerComponent(uuid, ani);

        ComponentShPtr ag = createDummy(*ani->as<Animat>());
        env.registerComponent(uuid, ag);

        ComponentShPtr rend = std::make_shared<Renderer>(*mo->as<MovingObject>(), RenderingMode::Square);
        env.registerComponent(uuid, rend);
      };
    }

  }
}
