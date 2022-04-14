
# include "Objects.hh"
# include "Renderer.hh"

/// @brief - The radius of an attractor.
# define ATTRACTOR_RADIUS 0.5f

/// @brief - The lifespan of the attractor in seconds.
# define ATTRACTOR_LIFESPAN_SECOND 60.0f

/// @brief - The scale to apply to the attractiveness.
# define ATTRACTOR_ATTRACTIVENESS 8.0f

namespace mas {
  namespace environment {

    Attractor::Attractor(float lifespan, float attractiveness) noexcept:
      m_lifespan(lifespan),
      m_attractiveness(attractiveness)
    {}

    float
    Attractor::attractiveness() const noexcept {
      return m_attractiveness;
    }

    void
    Attractor::simulate(const time::Manager& manager) {
      m_lifespan -= manager.lastStepDuration(time::Unit::Second);

      // In case the lifespan is expired, destroy the entity.
      if (m_lifespan < 0.0f) {
        destroyEntity(true);
      }
    }

    void
    spawnAttractor(Environment& env, const utils::Point2f& p, float attractiveness) noexcept {
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
        pge::colorGradient(olc::BLUE, olc::CYAN, 0.5f * (1.0f + attractiveness), pge::alpha::AlmostOpaque)
      );
      env.registerComponent(ent, rend);

      ComponentShPtr at = std::make_shared<Attractor>(ATTRACTOR_LIFESPAN_SECOND, ATTRACTOR_ATTRACTIVENESS * attractiveness);
      env.registerComponent(ent, at);
    }

  }
}
