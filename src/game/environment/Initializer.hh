#ifndef    INITIALIZER_HH
# define   INITIALIZER_HH

# include <core_utils/CoreObject.hh>
# include <maths_utils/Vector2.hh>

namespace mas {

  /// @brief - Forward declaration of the environment class.
  class Environment;

  namespace environment {

    class Initializer: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new initializer to generate the environment.
         * @param area - the spawn radius for elements.
         */
        Initializer(const utils::Vector2f& area);

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
        utils::Vector2f m_area;
    };

  }
}

#endif    /* INITIALIZER_HH */
