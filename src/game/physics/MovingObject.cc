
# include "MovingObject.hh"

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
      m_speed *= (1.0f - m_body.friction() * d);

      // Apply speed to modify position.
      utils::Vector2f tr = m_speed * d;

      m_area.x() += tr.x();
      m_area.y() += tr.y();

      verbose(
        "Moving object at " + m_area.toString() +
        " (f: " + m_force.toString() +
        ", acc: " + m_acceleration.toString() +
        ", speed: " + m_speed.toString() +
        ", friction: " + std::to_string((1.0f - m_body.friction()) * d) + ")"
      );

      // Reset the force: if it is applied continuously we
      // leave the other processes to reapply it.
      m_force = utils::Vector2f();
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
      m_force += f;
    }

  }
}
