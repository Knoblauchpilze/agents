#ifndef    INITIALIZER_HH
# define   INITIALIZER_HH

# include <core_utils/CoreObject.hh>
# include <core_utils/Uuid.hh>
# include <core_utils/RNG.hh>
# include <maths_utils/Point2.hh>
# include <maths_utils/Box.hh>

namespace mas {

  /// @brief - Forward declaration of the environment class.
  class Environment;

  namespace environment {

    /// @brief - A callback used to generate a random entity with a set
    /// of components.
    using EntityFactory = std::function<void(const utils::Uuid&, const utils::Point2f&, utils::RNG&, Environment&)>;

    class Initializer: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new initializer to generate the environment.
         * @param area - the spawn radius for elements.
         * @param factory - the factory associated to the initializer to
         *                  generate entities.
         */
        Initializer(const utils::Boxf& area,
                    EntityFactory factory);

        /**
         * @brief - Performs the initialization of the input environment.
         * @param env - the environment to initialize.
         */
        void
        operator()(Environment& env);

      private:

        /**
         * @brief - The spawn area for this initializer.
         */
        utils::Boxf m_area;

        /**
         * @brief - The callback used to generate entities.
         */
        EntityFactory m_factory;
    };

  }
}

#endif    /* INITIALIZER_HH */
