
# include "MovingObject.hh"

namespace mas {
  namespace environment {

    MovingObject::MovingObject(const utils::Boxf& area,
                               const RigidBody& body):
      utils::CoreObject("moving"),

      m_body(body),
      m_area(area),

      m_force(),
      m_acceleration(),
      m_speed()
    {
      setService("mas");
    }

    const utils::Boxf&
    MovingObject::bbox() const noexcept {
      return m_area;
    }

    const utils::Vector2f&
    MovingObject::acceleration() const noexcept {
      return m_acceleration;
    }

    const utils::Vector2f&
    MovingObject::speed() const noexcept {
      return m_speed;
    }

    bool
    MovingObject::intersects(const MovingObject& rhs) const noexcept {
      return m_area.intersects(rhs.m_area);
    }

    void
    MovingObject::applyForce(const utils::Vector2f& f) {
      utils::Vector2f fo = f;
      clampForce(fo);

      m_force += fo;
    }

    void
    MovingObject::simulate(const time::Manager& manager) {
      // Retrieve time delta in seconds.
      float d = manager.lastStepDuration(time::Unit::Second);

      // Apply force to modify acceleration if needed.
      if (m_body.infinitelyMassive()) {
        m_acceleration = (1.0f / m_body.mass()) * m_force;
      }

      // Apply acceleration to modify speed.
      m_speed += (m_acceleration * d);

      // Apply speed to modify position.
      utils::Vector2f tr = m_speed * d;

      m_area.x() += tr.x();
      m_area.y() += tr.y();
    }

    void
    MovingObject::clampForce(utils::Vector2f& /*force*/) const noexcept {
      // No clamping at this level.
    }

  }
}
