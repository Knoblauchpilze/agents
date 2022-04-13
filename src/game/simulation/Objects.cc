
# include "Objects.hh"
# include "Renderer.hh"

/// @brief - The radius of an attractor.
# define ATTRACTOR_RADIUS 0.5f

namespace mas {
  namespace environment {

    void
    spawnAttractor(Environment& env, const utils::Point2f& p) noexcept {
      // Create the entity.
      utils::Uuid ent = env.createEntity();

      // Register the components.
      utils::Boxf area(p.x(), p.y(), ATTRACTOR_RADIUS, ATTRACTOR_RADIUS);
      RigidBody rb(1.0f, 1.0f, 0.0f, area);

      ComponentShPtr mo = std::make_shared<MovingObject>(area, rb);
      env.registerComponent(ent, mo);

      ComponentShPtr rend = std::make_shared<Renderer>(
        *mo->as<MovingObject>(),
        RenderingMode::Square,
        olc::BLUE
      );
      env.registerComponent(ent, rend);
    }

  }
}
