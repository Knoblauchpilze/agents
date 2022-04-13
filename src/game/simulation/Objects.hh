#ifndef    OBJECTS_HH
# define   OBJECTS_HH

# include <maths_utils/Point2.hh>
# include "Environment.hh"

namespace mas {
  namespace environment {

    /**
     * @brief - Generate a new attractor at the specified position
     *          and register it in the environment.
     * @param env - the environment in which the attractor should
     *              be spawned.
     * @param p - the position where the object should be spawned.
     */
    void
    spawnAttractor(Environment& env, const utils::Point2f& p) noexcept;

  }
}

#endif    /* OBJECTS_HH */
