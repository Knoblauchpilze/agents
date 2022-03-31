
# include "CollisionSolver.hh"

namespace mas {
  namespace environment {

    CollisionSolver::CollisionSolver(Objects& objects) noexcept:
      utils::CoreObject("collisions"),

      m_objects(objects)
    {
      setService("mas");
    }

    bool
    CollisionSolver::solve() {
      Collisions c = detect();

      bool ok = true;
      for (unsigned id = 0u ; id < c.size() ; ++id) {
        ok &= solveCollision(c[id]);
      }

      return ok;
    }

    CollisionSolver::Collisions
    CollisionSolver::detect() const noexcept {
      Collisions out;

      // Detect whether each body is in collision with any
      // other body.
      for (unsigned id = 0u ; id < m_objects.size() ; ++id) {
        MovingObjectShPtr lhs = m_objects[id];

        // We only traverse the end of the list as the bodies
        // that are before the current one have been processed
        // when we were processing them.
        for (unsigned id2 = id ; id2 < m_objects.size() ; ++id2) {
          // Avoid self collisions.
          if (id == id2) {
            continue;
          }

          MovingObjectShPtr rhs = m_objects[id2];
          if (lhs->intersects(*rhs)) {
            out.push_back(Collision(lhs, rhs));
          }
        }
      }

      return out;
    }

    bool
    CollisionSolver::solveCollision(const Collision& /*col*/) const noexcept {
      /// TODO: Should handle the collision solving.
      return true;
    }

  }
}
