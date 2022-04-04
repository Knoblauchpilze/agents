#ifndef    FORCE_BASED_HH
# define   FORCE_BASED_HH

# include "Behavior.hh"

namespace mas {
  namespace environment {

    /// @brief - Convenience structure defining the information needed
    /// to define a repulsion behavior if an object gets too close from
    /// others.
    struct ForceBased {
      // The repulsion coefficient.
      float repulsion;

      /**
       * @brief - Compute the avoidance vector for the input position
       *          based on the input perceptions.
       * @param p - the position for which the avoidance vector should
       *            be computed.
       * @param perceptions - the list of perceptions to avoid.
       * @return - the avoidance vector.
       */
      utils::Vector2f
      computeAvoidanceVector(const utils::Point2f& p, const Perceptions& perceptions) noexcept;

      /**
       * @brief - Compute the repulsion force applied on `lhs` and
       *          `rhs` based on their position.$
       * @param lhs - the first position.
       * @param rhs - the second position.
       * @return - a float value representing the repulsion between
       *           the two positions.
       */
      float
      computeRepulsionForce(const utils::Point2f& lhs,
                            const utils::Point2f& rhs) noexcept;
    };

  }
}

#endif    /* FORCE_BASED_HH */
