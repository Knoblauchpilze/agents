
#include "RigidBody.h"

namespace environment
{
    namespace physics
    {
        unsigned int countRB(0u);

        RigidBody::RigidBody(const utils::sdl::Area& body, const double& density, const double& elasticity):
            m_area(body),
            m_density(density),
            m_mass(),
            m_elasticity(elasticity),
            m_force(),
            m_linearSpeed(),
            m_linearAcceleration(),
            m_listeners(),

            m_rb(countRB)
        {
            // Initialize constants from input values.
            setup();

            ++countRB;
        }

        RigidBody::~RigidBody()
        {
            // Nothing to do.
        }

        void RigidBody::addListener(RigidBodyListener* listener)
        {
            m_listeners.push_back(listener);
        }

        void RigidBody::applyTimeDelta(const time::TimeManager& manager)
        {
            // Retrieve time delta in seconds.
            const double timeDelta(manager.getLastStepDuration(environment::time::Unit::Second));
            // Apply force to modify acceleration.
            m_linearAcceleration = (1.0 / m_mass) * m_force;
            // Apply force to modify speed.
            m_linearSpeed += (m_linearAcceleration * timeDelta);

            const utils::Vector2d oldPos(getPosition());

            // Apply speed to modify position.
            const utils::Vector2d translation(m_linearSpeed * timeDelta);
            m_area.setX(m_area.getX() + translation.x());
            m_area.setY(m_area.getY() + translation.y());

            std::cout << "[RIGID " << m_rb << "] Force " << m_force << ", speed " << m_linearSpeed << ", p=" << getPosition() << " (old=" << oldPos << ") (mass=" << getMass() << ")" << std::endl;

            // Clear the force.
            m_force = utils::Vector2d();

            // Notify listeners.
            fireRigidBodyModification();
        }

        //==========

        void RigidBody::setup()
        {
            m_mass = m_density * m_area.getSurface();
        }

        void RigidBody::fireRigidBodyModification()
        {
            for (std::vector<RigidBodyListener*>::iterator listener = m_listeners.begin() ; listener != m_listeners.end() ; ++listener)
            {
                (*listener)->onRigidBodyUpdated();
            }
        }
    }
}
