#ifndef    PERCEPTION_HH
# define   PERCEPTION_HH

# include <vector>
# include "MovingObject.hh"

namespace mas {
  namespace environment {

    class Perception {
      public:

        /**
         * @brief - Create a new perception from the input object.
         * @param object - the object to be perceived.
         */
        Perception(const MovingObject& object);

        /**
         * @brief - Return the bounding box attached to the object.
         * @return - the bounding box attached to the perception.
         */
        const utils::Boxf&
        bbox() const noexcept;

      private:

        /**
         * @brief - The object attached to this perception.
         */
        const MovingObject& m_object;
    };

    /// @brief - A list of perceptions.
    using Perceptions = std::vector<Perception>;
  }
}

#endif    /* PERCEPTION_HH */
