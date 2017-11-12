#ifndef RIGIDBODY_HXX_INCLUDED
#define RIGIDBODY_HXX_INCLUDED

#include "ComparisonUtils.h"
#include "RigidBody.h"

namespace environment
{
    namespace physics
    {
        inline bool RigidBody::isInfinitelyMassive() const
        {
            return utils::comparison::doubleEqual(0.0, m_mass);
        }

        inline const double& RigidBody::getMass() const
        {
            return m_mass;
        }

        inline double RigidBody::getInverseMass() const
        {
            return (1.0 / m_mass);
        }

        inline const double& RigidBody::getElasticity() const
        {
            return m_elasticity;
        }

        inline const utils::Vector2d& RigidBody::getLinearSpeed() const
        {
            return m_linearSpeed;
        }

        inline const utils::Vector2d& RigidBody::getLinearAcceleration() const
        {
            return m_linearAcceleration;
        }

        inline utils::Vector2d RigidBody::getPosition() const
        {
            return utils::Vector2d(m_area.getX(), m_area.getY());
        }

        inline bool RigidBody::intersects(const RigidBody& other) const
        {
            return m_area.intersects(other.m_area);
        }

        inline void RigidBody::applyForce(const utils::Vector2d& force)
        {
            m_force += force;
        }

        inline void RigidBody::linearMove(const utils::Vector2d& speed)
        {
            m_linearSpeed += speed;
        }

        inline void RigidBody::translate(const utils::Vector2d& translation)
        {
            m_area.setX(m_area.getX() + translation.x());
            m_area.setY(m_area.getY() + translation.y());
        }

        inline const utils::sdl::Area& RigidBody::asArea() const
        {
            return m_area;
        }
    }
}

#endif // RIGIDBODY_HXX_INCLUDED
