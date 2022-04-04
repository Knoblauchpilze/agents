
# include "MovingObject.hh"

/// @brief - The decrease in speed due to friction and other
/// processing at each frame. This value is expressed in m/s2.
/// This correspond to an acceleration.
# define FRICTION_ACCELERATION 0.9f

namespace mas {
  namespace environment {

    MovingObject::MovingObject(const utils::Boxf& area,
                               const RigidBody& body):
      Component(Type::MovingObject),

      m_body(body),
      m_area(area),

      m_force(),
      m_acceleration(),
      m_speed()
    {
      setService("mas");
    }

    void
    MovingObject::update() {}

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
      if (!m_body.infinitelyMassive()) {
        m_acceleration = (1.0f / m_body.mass()) * m_force;
      }

      // Apply acceleration to modify speed.
      m_speed += (m_acceleration * d);

      // Account for friction.
      m_speed *= (1.0f - FRICTION_ACCELERATION * d);

      // Apply speed to modify position.
      utils::Vector2f tr = m_speed * d;

      m_area.x() += tr.x();
      m_area.y() += tr.y();

      log(
        "Moving object at " + m_area.toString() +
        " (f: " + m_force.toString() +
        ", acc: " + m_acceleration.toString() +
        ", speed: " + m_speed.toString() +
        ", friction: " + std::to_string((1.0f - FRICTION_ACCELERATION) * d) + ")",
        utils::Level::Verbose
      );

      // Reset the force: if it is applied continuously we
      // leave the other processes to reapply it.
      m_force = utils::Vector2f();
    }

    void
    MovingObject::clampForce(utils::Vector2f& /*force*/) const noexcept {
      // No clamping at this level.
    }

  }
}
