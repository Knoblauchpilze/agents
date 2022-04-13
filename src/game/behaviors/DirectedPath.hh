#ifndef    DIRECTED_PATH_HH
# define   DIRECTED_PATH_HH

# include "Behavior.hh"
# include <maths_utils/Point2.hh>

namespace mas {
  namespace environment {

    /// @brief - Convenience structure defining the information needed
    /// to define a behavior to reach a target.
    struct DirectedPath {
      // The target to reach.
      utils::Point2f target;

      // The distance to the target where we will consider that
      // we already reached it.
      float arrivalRadius;

      // The maximum acceleration possible.
      float maxAcceleration;

      /**
       * @brief - Compute a force to apply to reach the target.
       * @param p - the current position.
       * @return - the force to apply to reach the target.
       */
      utils::Vector2f
      motionToTarget(const utils::Point2f& p) const noexcept;

      /**
       * @brief - Compute a force to apply to reach the target.
       * @param x - the current position along the x axis.
       * @param y - the current position along the y axis.
       * @return - the force to apply to reach the target.
       */
      utils::Vector2f
      motionToTarget(float x, float y) const noexcept;
    };

  }
}

#endif    /* DIRECTED_PATH_HH */
