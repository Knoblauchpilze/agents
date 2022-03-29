
#include "DirectedFixedSpeedBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            DirectedFixedSpeedBehavior::DirectedFixedSpeedBehavior(const utils::Vector2d& position,
                                                                   const utils::sdl::Area& wanderingArea,
                                                                   const utils::Vector2d& desiredSpeed,
                                                                   const double& timeInterval):
                DirectedMotionBehavior(position, 0.1),
                m_timeInterval(timeInterval),
                m_desiredSpeed(desiredSpeed),
                m_speedTolerance(0.01),
                m_targetPicker(wanderingArea)
            {
                // Assign the new target
                pickNewTarget();
            }

            DirectedFixedSpeedBehavior::~DirectedFixedSpeedBehavior()
            {
                // Nothing to do.
            }

            std::vector<environment::agents::influences::InfluenceShPtr>
            DirectedFixedSpeedBehavior::perform(const std::vector<environment::perceptions::Perception>&)
            {
                // First compute the speed to achieve to reach the target with the specified time interval.
                utils::Vector2d outputSpeed(moveToTarget(getTarget(), m_timeInterval));
                // Compute the acceleration to reach the desired speed within the specified time interval.
                utils::Vector2d outputAcceleration(accelerateToSpeed(outputSpeed, m_timeInterval));
                //std::cout << "[FIXED] p=" << getPosition() << ", s=" << getSpeed() << ", a=" << getAcceleration() << ", t=" << getTarget() << " (motion=" << outputAcceleration << ")" << std::endl;
                // Transform this vector into an influence.
                return std::vector<agents::influences::InfluenceShPtr>(1u, createFromVector(outputAcceleration));
            }

            //====================

            bool DirectedFixedSpeedBehavior::reachedDesiredSpeed() const
            {
                return (getSpeed() - m_desiredSpeed).length() < m_speedTolerance;
            }

            utils::Vector2d DirectedFixedSpeedBehavior::moveToTarget(const utils::Vector2d& target, const double& secondsToReachTarget) const
            {
                // Currently we are moving at getSpeed() with an acceleration of getAcceleration().
                // We want to reach 'getTarget()' position within 'secondsToReachSpeed' seconds.
                // We know that p = p0 + (v0 + m) * t + a0 * 0.5 * t�
                // Let's substitute with known variables and we obtain:
                // target = getPosition() + (getSpeed() + m) * secondToReachTarget + getAcceleration() * 0.5 * secondToReachTarget�
                // Let's solve for m:
                // m = (target - getPosition() - getAcceleration() * 0.5 * secondToReachTarget�) / secondsToReachTarget - getSpeed()
                // Done !
                return (target - getPosition() - getAcceleration() * 0.5 * secondsToReachTarget) / secondsToReachTarget - getSpeed();
            }

            utils::Vector2d DirectedFixedSpeedBehavior::accelerateToSpeed(const utils::Vector2d& desired, const double& secondsToReachSpeed) const
            {
                // Currently we are moving at getSpeed() with an acceleration of getAcceleration().
                // We want to reach 'desired' speed within 'secondsToReachSpeed' seconds.
                // We know that v = v0 + (a0 + m) * t.
                // Let's substitute with known variables and we obtain:
                // desired = getSpeed() + (getAcceleration() + m) * secondsToReachSpeed
                // Let's solve for m:
                // m = (desired - getSpeed()) / secondsToReachSpeed - getAcceleration()
                // Done !
                return (desired - getSpeed()) / secondsToReachSpeed - getAcceleration();
            }

            void DirectedFixedSpeedBehavior::pickNewTarget()
            {
                setTarget(m_targetPicker());
            }
        }
    }
}
