
#include <chrono>
#include "WanderBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            const double WanderBehavior::sk_speedCorrectionTime(1.0);

            WanderBehavior::WanderBehavior(const utils::Vector2d& position,
                                           const utils::sdl::Area& wanderingArea,
                                           const double& desiredSpeed,
                                           const double& distanceToDeccelerate):
                DirectedMotionBehavior(position, 0.1),
                m_random(wanderingArea),
                m_hasTarget(false),
                m_target(),
                m_distanceToDeccelerate(distanceToDeccelerate),
                m_desiredSpeed(desiredSpeed)
            {
                // Pick a new target.
                pickNewTarget();
            }

            WanderBehavior::~WanderBehavior()
            {
                // Nothing to do.
            }

            bool WanderBehavior::isComplete() const
            {
                return false;
            }

            //==============

            bool WanderBehavior::hasTarget() const
            {
                return m_hasTarget && !arrivedToTarget();
            }

            const utils::Vector2d& WanderBehavior::getTarget() const
            {
                return m_target;
            }

            void WanderBehavior::pickNewTarget()
            {
                // Pick a target.
                m_target = m_random();
                // Compute a new one if the distance is not sufficient.
                while (computeDistanceToTarget() < getDistanceToArrival())
                {
                    m_target = m_random();
                }
                std::cout << "[WANDER] Pick target " << m_target << std::endl;
                m_hasTarget = true;
            }

            utils::Vector2d WanderBehavior::computeMotionForceToTarget() const
            {
                // Compute the direction of the force to apply.
                const double distanceToTarget(computeDistanceToTarget());
                double speedMagnitude(getSpeed().length());
                const utils::Vector2d directionToTarget((getTarget() - getPosition()).normalized());
                // Let's compute the speed we want, without basing our computations on the current speed: this way we can provide
                // independent behaviours which can play nicely together.
                // So we want to achieve a m_desired speed along the directionToTarget except if we are close enough to the target.
                // In addition to that, we must take care of the case where we have a limit which is greater than the authorized
                // value (shall it be m_desiredSpeed or theoreticalSpeed) but in the wrong direction. In this case, we need first to negate the
                // speed, and then add the contribution to operate a motion in the general direction of the target.
                // Assume maximum speed.
                double forceMagnitude(0.0);

                //double theo(m_desiredSpeed);

                // And let's check for the valid motion.
                const bool validMotion(directionToTarget * getSpeed() > 0.0);
                if (!validMotion)
                {
                    // We do not move in the direction of the target, so we must first stop: little trap here as the force magnitude is applied
                    // along the position to target vector, and already contains a 'hidden' negative sign.
                    forceMagnitude = speedMagnitude;
                    // In this case, we handled some of the magnitude (basically we gave instructions to make this object stop).
                    // But we should also handle some additional motion to move in the direction of the target.
                    // Let's subtract the part of the speed which we just handled.
                    speedMagnitude = 0.0;
                }
                // We should also check the input speed magnitude.
                if (validMotion && speedMagnitude > m_desiredSpeed)
                {
                    // We do want to decelerate to reach the desired speed.
                    forceMagnitude = -(speedMagnitude - m_desiredSpeed);
                    // We did handle part of the speed magnitude, let's remove that.
                    speedMagnitude -= forceMagnitude;
                }
                // Now we know that:
                //  -either the speed was in the general direction of the target and in this case both (theoreticalSpeed - speedMagnitude) and
                //   (m_desiredSpeed - speedMagnitude) will be valid (i.e. positive)
                //  -or we had a valid motion within the speed constraints of this object
                // In both scenario we can safely proceed to the rest of the computations.
                // First, check distance to the target.
                if (distanceToTarget < m_distanceToDeccelerate)
                {
                    // We should have a speed decreasing linearly from m_distanceToDeccelerate to 0.0.
                    // Compute the theoretical speed at this distance.
                    const double slope((m_desiredSpeed - 0.0) / (m_distanceToDeccelerate - 0.0));
                    const double abscissa(distanceToTarget - 0.0);
                    const double offset(0.0);
                    const double theoreticalSpeed(offset + abscissa * slope);
                    // We can compute the force to obtain the desired speed.
                    forceMagnitude += (theoreticalSpeed - speedMagnitude);

                    //theo = theoreticalSpeed;
                }
                // Then check for maximum cruising speed.
                else
                {
                    // Reduce the speed or accelerate based on the difference between the desired speed and the current.
                    forceMagnitude += (m_desiredSpeed - speedMagnitude);
                }
                // We computed the magnitude of the force to

                //std::cout << "[WANDER] p=" << getPosition() << ", t=" << getTarget() << ", d= " << distanceToTarget << ", s=" << getSpeed() << ", t=" << theo << ", f=" << forceMagnitude << ", u=" << directionToTarget << std::endl;
                // Return the built-in force.
                return forceMagnitude * directionToTarget;
            }
        }
    }
}
