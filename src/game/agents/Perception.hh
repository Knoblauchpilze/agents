#ifndef    PERCEPTION_HH
# define   PERCEPTION_HH

# include <vector>
# include "MovingObject.hh"
# include "UserData.hh"

namespace mas {
  namespace environment {

    class Perception {
      public:

        /**
         * @brief - Create a new perception from the input object and
         *          the user data.
         * @param object - the object to be perceived.
         * @param data - the user data attached to the object: may be
         *               null in case no data is attached.
         */
        Perception(const MovingObject& object, const UserData* data = nullptr);

        /**
         * @brief - Return the bounding box attached to the object.
         * @return - the bounding box attached to the perception.
         */
        const utils::Boxf&
        bbox() const noexcept;

        /**
         * @brief - Whether or not this perception is associated with
         *          some sort of user data.
         * @return - `true` if the perception has some user data.
         */
        bool
        hasUserData() const noexcept;

        /**
         * @brief - Convert the user data attached to this perception
         *          as the requested pointer type. In case the data does
         *          not have the correct type, then the return value
         *          will be null.
         * @return - the user data as a pointer to the dedicated type.
         */
        template <typename T>
        const T*
        as() const noexcept;

      private:

        /**
         * @brief - The object attached to this perception.
         */
        const MovingObject& m_object;

        /**
         * @brief - The user data attached to the perception.
         */
        const UserData* m_data;
    };

    /// @brief - A list of perceptions.
    using Perceptions = std::vector<Perception>;
  }
}

# include "Perception.hxx"

#endif    /* PERCEPTION_HH */
