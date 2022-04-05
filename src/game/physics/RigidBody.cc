
# include "RigidBody.hh"
# include <algorithm>

namespace mas {
  namespace environment {

    RigidBody::RigidBody(float mass,
                         float elasticity,
                         float friction,
                         const utils::Boxf& area) noexcept:
      m_area(area),

      m_mass(mass),
      m_elasticity(elasticity),
      m_friction(std::clamp(friction, 0.0f, 1.0f))
    {}

    bool
    RigidBody::infinitelyMassive() const noexcept {
      return m_mass < 0.0f;
    }

    float
    RigidBody::mass() const noexcept {
      return m_mass;
    }

    float
    RigidBody::elasticity() const noexcept {
      return m_elasticity;
    }

    float
    RigidBody::friction() const noexcept {
      return m_friction;
    }

  }
}
