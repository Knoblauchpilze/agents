
# include "Initializer.hh"
# include <core_utils/RNG.hh>
# include "Environment.hh"
# include "Animat.hh"
# include "Renderer.hh"
# include "Dummy.hh"

namespace mas {
 namespace environment {

    Initializer::Initializer(unsigned agentsCount,
                             Spawner spawner,
                             EntityFactory factory):
      utils::CoreObject("initializer"),

      m_agentsCount(agentsCount),
      m_spawner(spawner),
      m_factory(factory)
    {
      setService("mas");
    }

    void
    Initializer::setup(Environment& env) {
      // Create a RNG.
      utils::RNG& rng = env.rng();

      log("Seeding environment with " + std::to_string(m_agentsCount) + " agent(s)", utils::Level::Info);

      unsigned id = 0u;
      while (id < m_agentsCount) {
        // Create the entity and use the factory to attach the
        // corresponding component. We pick the position here
        // as we know the area where entities should be spawned.
        utils::Point2f p = m_spawner(rng);

        log("Spawning agent at " + p.toString(), utils::Level::Info);
        utils::Uuid uuid = env.createEntity();
        m_factory(uuid, p, rng, env);

        ++id;
      }
    }

 }
}
