
# include "PhysicEngine.hh"
# include <algorithm>

namespace {

  intptr_t
  generateKey(const mas::environment::MovingObject* b) noexcept {
    if (b == nullptr) {
      return 0u;
    }

    return reinterpret_cast<intptr_t>(b);
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
    PhysicEngine::registerObject(MovingObject* obj) {
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
    PhysicEngine::unregisterObject(MovingObject* obj) {
      if (obj == nullptr) {
        return;
      }

      // Can only remove an object in case it is registered.
      Key k = generateKey(obj);
      if (m_keys.count(k) == 0u) {
        return;
      }

      unsigned s = m_objects.size();

      Objects::iterator it = std::remove_if(m_objects.begin(), m_objects.end(),
        [&k](const MovingObject* o) {
          return generateKey(o) == k;
        }
      );
      m_objects.erase(it, m_objects.end());
      m_keys.erase(k);

      if (s > 0u && m_objects.size() != s - 1u) {
        warn("Removed " + std::to_string(s - m_objects.size()) + " object(s) when removing object " + obj->getName());
      }
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
