#ifndef    USER_DATA_HH
# define   USER_DATA_HH

# include <vector>
# include "Component.hh"

namespace mas {
  namespace environment {

    class UserData: public Component {
      public:

        /**
         * @brief - Create a default object with no attached data.
         */
        UserData() noexcept;

        /**
         * @brief - Virtual destructor to allow polymorphism.
         */
        virtual ~UserData() noexcept;

        /**
         * @brief - Implementation of the interface method to handle
         *          the update of the component. Nothing is done at
         *          this level.
         */
        void
        simulate(const time::Manager& manager) override;
    };

  }
}

#endif    /* USER_DATA_HH */
