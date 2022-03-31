
# include "RigidBody.hh"

namespace mas {
  namespace environment {

    RigidBody::RigidBody(float mass,
                         float elasticity,
                         const utils::Boxf& area) noexcept:
      m_area(area),

      m_mass(mass),
      m_elasticity(elasticity)
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

  }
}
