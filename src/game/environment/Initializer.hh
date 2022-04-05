#ifndef    INITIALIZER_HH
# define   INITIALIZER_HH

# include <core_utils/CoreObject.hh>
# include <core_utils/Uuid.hh>
# include <core_utils/RNG.hh>
# include <maths_utils/Point2.hh>

namespace mas {

  /// @brief - Forward declaration of the environment class.
  class Environment;

  namespace environment {

    /// @brief - A callback used to generate a random entity with
    /// a set of components.
    using EntityFactory = std::function<void(const utils::Uuid&, const utils::Point2f&, utils::RNG&, Environment&)>;

    /// @brief- A callback to pick a new random position to spawn
    /// an agent.
    using Spawner = std::function<utils::Point2f(utils::RNG&)>;

    class Initializer: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new initializer to generate the environment.
         * @param agentsCount - the number of agents to spawn.
         * @param spawner - the callback to use to generate positions to
         *                  spawn agents.
         * @param factory - the factory associated to the initializer to
         *                  generate entities.
         */
        Initializer(unsigned agentsCount,
                    Spawner spawner,
                    EntityFactory factory);

        /**
         * @brief - Performs the initialization of the input environment.
         * @param env - the environment to initialize.
         */
        void
        setup(Environment& env);

      private:

        /**
         * @brief - The number of agents to spawn.
         */
        unsigned m_agentsCount;

        /**
         * @brief - The callback to use to generate a position
         *          to spawn a new agent.
         */
        Spawner m_spawner;

        /**
         * @brief - The callback used to generate entities.
         */
        EntityFactory m_factory;
    };

  }
}

#endif    /* INITIALIZER_HH */
