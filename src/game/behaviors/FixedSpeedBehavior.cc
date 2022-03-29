
#include "FixedSpeedBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            FixedSpeedBehavior::FixedSpeedBehavior(const utils::Vector2d& position,
                                                   const utils::Vector2d& desiredSpeed,
                                                   const double& timeInterval):
                MotionBehavior(position, 1.0),
                m_timeInterval(timeInterval),
                m_desiredSpeed(desiredSpeed),
                m_speedTolerance(0.001)
            {
                // Nothing to do.
            }

            FixedSpeedBehavior::~FixedSpeedBehavior()
            {
                // Nothing to do.
            }

            bool FixedSpeedBehavior::isComplete() const
            {
                return reachedDesiredSpeed();
            }

            std::vector<environment::agents::influences::InfluenceShPtr>
            FixedSpeedBehavior::perform(const std::vector<environment::perceptions::Perception>&)
            {
                // Compute the acceleration to reach the desired speed within the specified time interval.
                utils::Vector2d outputAcceleration(accelerateToSpeed(m_desiredSpeed, m_timeInterval));
                // Transform this vector into an influence.
                return std::vector<agents::influences::InfluenceShPtr>(1u, createFromVector(outputAcceleration));
            }

            //====================

            bool FixedSpeedBehavior::reachedDesiredSpeed() const
            {
                return (getSpeed() - m_desiredSpeed).length() < m_speedTolerance;
            }

            utils::Vector2d FixedSpeedBehavior::accelerateToSpeed(const utils::Vector2d& desired, const double& secondsToReachSpeed) const
            {
                // Currently we are moving at getSpeed() with no acceleration (or so we assume).
                // We want to reach 'desired' speed within 'secondsToReachSpeed' seconds.
                // We know that v = v0 + (a0 + m) * t.
                // Let's substitute with known variables and we obtain:
                // desired = getSpeed() + (0.0 + m) * secondsToReachSpeed
                // Let's solve for m:
                // m = (desired - getSpeed()) / secondsToReachSpeed - 0.0
                // Done !
                return (desired - getSpeed()) / secondsToReachSpeed;
            }
        }
    }
}
