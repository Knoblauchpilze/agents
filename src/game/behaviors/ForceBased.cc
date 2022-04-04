
# include "ForceBased.hh"
# include <maths_utils/ComparisonUtils.hh>
# include "Utils.hh"

namespace mas {
  namespace environment {

    utils::Vector2f
    ForceBased::computeAvoidanceVector(const utils::Point2f& p, const Perceptions& perceptions) noexcept {
      utils::Vector2f out;

      for (unsigned id = 0u ; id < perceptions.size() ; ++id) {
        // Get the nearest point for the current object.
        utils::Point2f nearest = nearestPoint(p, perceptions[id].bbox());

        // Compute repulsion coefficient.
        float repulsion = computeRepulsionForce(p, nearest);

        // The force is applied on the opposite vector
        // from the object to the perception
        utils::Point2f toP = p - nearest;
        out += (toP.normalized() * repulsion);
      }

      return out;
    }

    float
    ForceBased::computeRepulsionForce(const utils::Point2f& lhs,
                                      const utils::Point2f& rhs) noexcept
    {
      float d = (rhs - lhs).length();

      // No repulsion force in case the objects are at
      // the same position: this avoids having numeric
      // instabilities.
      if (utils::fuzzyEqual(d, 0.0f)) {
        return 0.0f;
      }

      return repulsion / std::log(1.0f + d);
    }

  }
}
