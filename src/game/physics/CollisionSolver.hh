#ifndef    COLLISION_SOLVER_HH
# define   COLLISION_SOLVER_HH

# include <vector>
# include <core_utils/CoreObject.hh>
# include "MovingObject.hh"

namespace mas {
  namespace environment {

    /// @brief - A collection of moving objects.
    using Objects = std::vector<MovingObject*>;

    class CollisionSolver: public utils::CoreObject {
      public:

        /**
         * @brief - Builds a new solver with the specified set of
         *          moving objects.
         * @param objects - the list of moving objects to solve.
         */
        CollisionSolver(Objects& objects) noexcept;

        /**
         * @brief - Solve the collisions which might be happening in
         *          the list of bodies.
         * @return - `true` if we could solve all collisions.
         */
        bool
        solve();

      private:

        /// @brief - A collision: this represents a pair of objects which
        /// are in collision.
        using Collision = std::pair<MovingObject*, MovingObject*>;

        /// @brief - A list of potential collisions.
        using Collisions = std::vector<Collision>;

        /**
         * @brief - Detect the potential collisions within the list of
         *          objects passed to the solver.
         * @return - the list of potential collisions.
         */
        Collisions
        detect() const noexcept;

        /**
         * @brief - Solve the input collision.
         * @param collision - the collision to solve.
         * @return - `true` if the collision could be solved.
         */
        bool
        solveCollision(const Collision& col) const noexcept;

      private:

        /**
         * @brief - The list of objects that may be in collision and
         *          for which we should solve collisions.
         */
        Objects& m_objects;
    };

  }
}

#endif    /* COLLISION_SOLVER_HH */
