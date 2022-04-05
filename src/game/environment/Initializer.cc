
# include "Initializer.hh"
# include <core_utils/RNG.hh>
# include "Environment.hh"
# include "Animat.hh"
# include "Renderer.hh"
# include "Dummy.hh"

/// @brief - How many objects are spawned at the beginning.
# define AGENTS_COUNT 1u

namespace mas {
 namespace environment {

    Initializer::Initializer(const utils::Boxf& area,
                             EntityFactory factory):
      utils::CoreObject("initializer"),

      m_area(area),
      m_factory(factory)
    {
      setService("mas");
    }

    void
    Initializer::operator()(Environment& env) {
      // Create a RNG.
      utils::RNG& rng = env.rng();

      log("Generating " + std::to_string(AGENTS_COUNT) + " element(s) within " + m_area.toString(), utils::Level::Info);

      unsigned id = 0u;
      while (id < AGENTS_COUNT) {
        // Create the entity and use the factory to attach the
        // corresponding component. We pick the position here
        // as we know the area where entities should be spawned.
        utils::Point2f p;
        p.x() = rng.rndFloat(m_area.getLeftBound(), m_area.getRightBound());
        p.y() = rng.rndFloat(m_area.getBottomBound(), m_area.getTopBound());

        log("Spawning agent at " + p.toString(), utils::Level::Info);

        utils::Uuid uuid = env.createEntity();

        m_factory(uuid, p, rng, env);

        ++id;
      }
    }

 }
}
