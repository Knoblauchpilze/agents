
# include "DirectedPath.hh"

namespace mas {
  namespace environment {

    utils::Vector2f
    DirectedPath::motionToTarget(const utils::Point2f& p) const noexcept {
      // Compute the direction of the force to apply.
      float d = (target - p).length();
      utils::Vector2f toTarget = (target - p).normalized();

      // If we are close enough to the target, we stop
      // so as to not overshoot.
      if (d <= arrivalRadius) {
        return utils::Vector2f();
      }

      // Apply a certain force based on the maximum
      // acceleration we can reach.
      return maxAcceleration * toTarget;
    }

    utils::Vector2f
    DirectedPath::motionToTarget(float x, float y) const noexcept {
      return motionToTarget(utils::Point2f(x, y));
    }

  }
}
