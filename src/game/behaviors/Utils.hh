#ifndef    UTILS_HH
# define   UTILS_HH

# include <maths_utils/Point2.hh>
# include <maths_utils/Box.hh>

namespace mas {
  namespace environment {

    /**
     * @brief - Return the nearest point from the input position
     *          to the area but still belonging to it.
     * @param p - the point from which the nearest point should
     *            be computed.
     * @param area - the area from which the nearest point should
     *               be computed.
     * @return - a point representing the nearest position.
     */
    utils::Point2f
    nearestPoint(const utils::Point2f& p, const utils::Boxf& area) noexcept;

  }
}

#endif    /* UTILS_HH */
