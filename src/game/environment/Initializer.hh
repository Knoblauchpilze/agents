#ifndef    INITIALIZER_HH
# define   INITIALIZER_HH

# include <core_utils/CoreObject.hh>
# include <maths_utils/Box.hh>

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
        Initializer(const utils::Boxf& area);

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
    };

  }
}

#endif    /* INITIALIZER_HH */
