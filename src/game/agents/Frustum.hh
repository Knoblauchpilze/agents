#ifndef    FRUSTUM_HH
# define   FRUSTUM_HH

# include <maths_utils/Box.hh>
# include "MovingObject.hh"

namespace mas {
  namespace environment {

    class Frustum {
      public:

        /**
         * @brief - Create a new frustum with the specified area.
         * @param area - the area covered by the frustum.
         */
        Frustum(const utils::Boxf& area) noexcept;

        /**
         * @brief - Return whether the object is visible for this
         *          frustum.
         * @param obj - the object to check for visibility.
         * @return - `true` if the object is visible.
         */
        bool
        visible(const MovingObject& obj) const noexcept;

      private:

        /**
         * @brief - The area attached to this frustum.
         */
        utils::Boxf m_area;
    };

  }
}

#endif    /* FRUSTUM_HH */
