
#include <chrono>
#include "DirectedForceBasedBehavior.h"
#include "ComparisonUtils.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            DirectedForceBasedBehavior::DirectedForceBasedBehavior(const utils::Vector2d& position, const utils::sdl::Area& wanderingArea):
                DirectedMotionBehavior(position, 0.1),
                m_rng(),
                m_wanderingArea(wanderingArea)
            {
                // Assign the target.
                pickNewTarget();
            }

            DirectedForceBasedBehavior::~DirectedForceBasedBehavior()
            {
                // Nothing to do.
            }

            std::vector<std::shared_ptr<environment::agents::influences::Influence>>
            DirectedForceBasedBehavior::perform(const VectorOfPerceptions& perceptions)
            {
                // Compute a vector used to reach the target.
                utils::Vector2d motionToTarget(computeMotionVectorToTarget());
                // Compute an avoidance vector based on the perceptions.
                utils::Vector2d avoidanceForce(computeAvoidanceVector(perceptions));
                // Combine both into an influence
                utils::Vector2d totalMotion(motionToTarget + avoidanceForce);
                return std::vector<agents::influences::InfluenceShPtr>(1u, createFromVector(totalMotion));
            }

            //==================

            void DirectedForceBasedBehavior::pickNewTarget()
            {
                setTarget(m_wanderingArea());
            }

            utils::Vector2d DirectedForceBasedBehavior::computeAvoidanceVector(const VectorOfPerceptions& perceptions) const
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

            double DirectedForceBasedBehavior::computeRepulsionForce(const utils::Vector2d& current, const utils::Vector2d& other) const
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
