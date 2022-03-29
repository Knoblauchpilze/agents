
#include <limits>
#include "MotionBehavior.h"
#include "LinearMotionInfluence.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            MotionBehavior::MotionBehavior(const utils::Vector2d& position, const double& maxForce):
                Behavior(),
                m_position(position),
                m_speed(),
                m_acceleration(),
                m_maxForce(maxForce)
            {
                // Nothing to do.
            }

            MotionBehavior::~MotionBehavior()
            {
                // Nothing to do.
            }

            //=========

            void MotionBehavior::setPosition(const utils::Vector2d& position)
            {
                m_position = position;
            }

            void MotionBehavior::setSpeed(const utils::Vector2d& speed)
            {
                m_speed = speed;
            }

            //=========

            const utils::Vector2d& MotionBehavior::getPosition() const
            {
                return m_position;
            }

            const utils::Vector2d& MotionBehavior::getSpeed() const
            {
                return m_speed;
            }

            const utils::Vector2d& MotionBehavior::getAcceleration() const
            {
                return m_acceleration;
            }

            const double& MotionBehavior::getMaxForce() const
            {
                return m_maxForce;
            }

            bool MotionBehavior::isMoving(const double& threshold) const
            {
                return (m_speed.lengthSquared() > threshold * threshold);
            }

            environment::agents::influences::InfluenceShPtr MotionBehavior::createFromVector(utils::Vector2d& force) const
            {
                // Clamp this input acceleration if needed.
                const double forceMagnitude(force.length());
                if (forceMagnitude > m_maxForce)
                {
                    force *= (m_maxForce / forceMagnitude);
                }
                return std::make_shared<agents::influences::LinearMotionInfluence>(force);
            }
        }
    }
}
