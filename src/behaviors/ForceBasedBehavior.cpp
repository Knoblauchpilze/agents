
#include "ComparisonUtils.h"
#include "ForceBasedBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            ForceBasedBehavior::ForceBasedBehavior(const utils::Vector2d& position):
                MotionBehavior(position)
            {
                // Nothing to do.
            }

            ForceBasedBehavior::~ForceBasedBehavior()
            {
                // Nothing to do.
            }

            std::vector<std::shared_ptr<environment::agents::influences::Influence>>
            ForceBasedBehavior::perform(const VectorOfPerceptions& perceptions)
            {
                // Compute an avoidance vector based on the perceptions.
                utils::Vector2d avoidanceForce(computeAvoidanceVector(perceptions));
                // Return it as an influence
                return std::vector<agents::influences::InfluenceShPtr>(1u, createFromVector(avoidanceForce));
            }

            //==================

            utils::Vector2d ForceBasedBehavior::computeAvoidanceVector(const VectorOfPerceptions& perceptions) const
            {
                utils::Vector2d resultingForce;
                const utils::Vector2d& position(getPosition());
                for (VectorOfPerceptions::const_iterator perception = perceptions.cbegin() ; perception != perceptions.cend() ; ++perception)
                {
                    utils::Vector2d nearestPoint(getNearestPoint(position, *perception));
                    const double repulsion(computeRepulsionForce(position, nearestPoint));
                    utils::Vector2d otherToPosition(position - nearestPoint);
                    resultingForce += (otherToPosition.normalized() * repulsion);
                }
                return resultingForce;
            }

            double ForceBasedBehavior::computeRepulsionForce(const utils::Vector2d& current, const utils::Vector2d& other) const
            {
                const double distanceToObject((other - current).length());
                if (utils::comparison::doubleEqual(distanceToObject, 0.0))
                {
                    return 0.0;
                }
                return (0.02 / std::log(1.0 + distanceToObject));
            }
        }
    }
}
