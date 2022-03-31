
# include "PhysicEngine.hh"
# include <algorithm>

namespace {

  intptr_t
  generateKey(const mas::environment::MovingObjectShPtr& b) noexcept {
    if (b == nullptr) {
      return 0u;
    }

    return reinterpret_cast<intptr_t>(b.get());
  }

}

namespace mas {
  namespace environment {

    PhysicEngine::PhysicEngine():
      utils::CoreObject("physic"),

      m_objects(),
      m_keys()
    {
      setService("mas");
    }

    void
    PhysicEngine::registerObject(MovingObjectShPtr obj) {
      if (obj == nullptr) {
        return;
      }

      // Only register a body once.
      Key k = generateKey(obj);
      if (m_keys.count(k) > 0u) {
        return;
      }

      m_objects.push_back(obj);
      m_keys.insert(k);
    }

    void
    PhysicEngine::unregisterObject(MovingObjectShPtr obj) {
      if (obj == nullptr) {
        return;
      }

      // Can only remove an object in case it is registered.
      Key k = generateKey(obj);
      if (m_keys.count(k) == 0u) {
        return;
      }

      Objects::iterator it = std::remove_if(m_objects.begin(), m_objects.end(),
        [&k](const MovingObjectShPtr& o) {
          return generateKey(o) == k;
        }
      );
      m_objects.erase(it);
      m_keys.erase(k);
    }

    void
    PhysicEngine::simulate(const time::Manager& manager) {
      // Solve collisions.
      CollisionSolver cs(m_objects);
      if (!cs.solve()) {
        warn("Failed to solve all collisions after " + std::to_string(manager.elapsed()) + " second(s)");
      }
    }

  }
}
