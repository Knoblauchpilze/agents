
#include "DirectedMotionBehavior.h"
#include "ComparisonUtils.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            DirectedMotionBehavior::DirectedMotionBehavior(const utils::Vector2d& position, const double& distanceToArrival):
                MotionBehavior(position, 1.0),
                m_distanceToArrival(distanceToArrival)
            {
                // Nothing to do.
            }

            DirectedMotionBehavior::~DirectedMotionBehavior()
            {
                // Nothing to do.
            }

            bool DirectedMotionBehavior::isComplete() const
            {
                return arrivedToTarget();
            }

            std::vector<environment::agents::influences::InfluenceShPtr>
            DirectedMotionBehavior::perform(const VectorOfPerceptions&)
            {
                // Pick a new target if needed.
                if (!hasTarget())
                {
                    pickNewTarget();
                }
                // Create the vector to target.
                utils::Vector2d forceToTarget(computeMotionForceToTarget());

                //std::cout << "[WANDER] p=" << getPosition() << ", t=" << getTarget() << ", s=" << getSpeed() << ", f=" << forceToTarget << std::endl;

                return std::vector<agents::influences::InfluenceShPtr>(1u, createFromVector(forceToTarget));
            }

            //==============

            const double& DirectedMotionBehavior::getDistanceToArrival() const
            {
                return m_distanceToArrival;
            }

            bool DirectedMotionBehavior::arrivedToTarget() const
            {
                return (computeDistanceToTarget() < m_distanceToArrival);
            }

            double DirectedMotionBehavior::computeDistanceToTarget() const
            {
                return (getPosition() - getTarget()).length();
            }
        }
    }
}
