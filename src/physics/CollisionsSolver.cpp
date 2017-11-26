
#include <algorithm>
#include "CollisionsSolver.h"

namespace environment
{
    namespace physics
    {
        CollisionsSolver::CollisionsSolver()
        {
            // Nothing to do.
        }

        CollisionsSolver::~CollisionsSolver()
        {
            // Nothing to do.
        }

        void CollisionsSolver::solve(const std::vector<RigidBodyShPtr>& bodies)
        {
            // First, detect collisions.
            std::vector<PotentialCollision> collisions;
            collisionsDetection(bodies, collisions);
            // Sort and remove duplicated collisions.
            sortAndFilterCollisions(collisions);
            // Solve each collision.
            solveCollisions(collisions);
        }

        //==============

        void CollisionsSolver::collisionsDetection(const std::vector<RigidBodyShPtr>& bodies, std::vector<PotentialCollision>& collisions) const
        {
            collisions.clear();
            for (std::vector<RigidBodyShPtr>::const_iterator mainBody = bodies.cbegin() ; mainBody != bodies.cend() ; ++mainBody)
            {
                for (std::vector<RigidBodyShPtr>::const_iterator secondaryBody = bodies.cbegin() ; secondaryBody != bodies.cend() ; ++secondaryBody)
                {
                    // Avoid collision with self.
                    if (mainBody == secondaryBody)
                    {
                        continue;
                    }

                    //std::cout << "[SOLVER] " << (*mainBody)->m_rb << ": " << (*mainBody)->asArea().getX() << "x" << (*mainBody)->asArea().getY() << ", " << (*secondaryBody)->m_rb << ": " << (*secondaryBody)->asArea().getX() << "x" << (*secondaryBody)->asArea().getY() << ", inter=" << (*mainBody)->intersects(**secondaryBody) << std::endl;


                    // Detect collisions.
                    if ((*mainBody)->intersects(**secondaryBody))
                    {
                        collisions.push_back(std::make_pair(*mainBody, *secondaryBody));
                    }
                }
            }
        }

        void CollisionsSolver::sortAndFilterCollisions(std::vector<PotentialCollision>& collisions) const
        {
            // Sort the input vector of pairs.
            std::sort(collisions.begin(), collisions.end(),
                [](const PotentialCollision& lhs, const PotentialCollision& rhs) {
                    if(lhs.first < rhs.first)
                    {
                        return true;
                    }
                    if(lhs.first == rhs.first)
                    {
                        return lhs.second < rhs.second;
                    }
                    return false;
            });

            // Remove duplicates.
            std::vector<PotentialCollision> uniqueCollisions;
            unsigned int indexCollision(0u);
            while (indexCollision < collisions.size())
            {
                const PotentialCollision& currentCollision(collisions[indexCollision]);
                uniqueCollisions.push_back(currentCollision);

                ++indexCollision;
                while (indexCollision < collisions.size())
                {
                    const PotentialCollision& potentialDuplicate(collisions[indexCollision]);

                    if (potentialDuplicate.first != currentCollision.second ||
                        potentialDuplicate.second != currentCollision.first)
                    {
                        // Found a new collision, no more duplicates for the current collision.
                        break;
                    }
                    ++indexCollision;
                }
            }
            collisions.swap(uniqueCollisions);
        }

        void CollisionsSolver::solveCollisions(const std::vector<PotentialCollision>& collisions) const
        {
            // Traverse each collision.
            for (std::vector<PotentialCollision>::const_iterator collision = collisions.cbegin() ; collision != collisions.cend() ; ++collision)
            {
                const PotentialCollision& currentCollision(*collision);

                /*std::cout << "------" << std::endl;
                std::cout << "[FIX] Solving collision between:" << std::endl;
                std::cout << "[FIX] p1=" << currentCollision.first->getPosition() << ", m1=" << currentCollision.first->getMass() << ", v1=" << currentCollision.second->getLinearSpeed() << std::endl;
                std::cout << "[FIX] p2=" << currentCollision.second->getPosition() << ", m2=" << currentCollision.second->getMass() << ", v2=" << currentCollision.second->getLinearSpeed() << std::endl;*/

                // We need to compute two information: the collision normal and the penetration depth (i.e. how far both objects have inter-penetrated).
                const utils::Vector2d collisionNormal(computeCollisionNormal(currentCollision));
                const utils::Vector2d penetrationDepth(computePenetrationDepth(currentCollision));

                // Compute the impulse based on both colliding objects' properties and the above properties.
                const double impulseMagnitude(computeCollisionImpulse(currentCollision, collisionNormal));
                // Deduce the impulse vector from this impulse and the collision's normal.
                utils::Vector2d impulse(impulseMagnitude * collisionNormal);

                //std::cout << "[FIX] n=" << collisionNormal << " depth=" << penetrationDepth << ", reaction=" << impulseMagnitude << " (impulse=" << impulse << ")" << std::endl;

                // Now we can modify the speed of each rigid body accordingly.
                // We know that the normal is computed so that currentCollision.first is moving in the direction of the normal.
                const double slop(0.01);
                if (penetrationDepth.length() > slop)
                {
                    const utils::Vector2d correction(penetrationDepth.length() * collisionNormal / (currentCollision.first->getInverseMass() + currentCollision.second->getInverseMass()));

                    //std::cout << "[FIX] correction1=" << -correction << ", correction2=" << correction << std::endl;

                    currentCollision.first->linearMove(-currentCollision.first->getInverseMass() * impulse);
                    currentCollision.second->linearMove(currentCollision.second->getInverseMass() * impulse);
                    currentCollision.first->translate(-currentCollision.first->getInverseMass() * correction);
                    currentCollision.second->translate(currentCollision.second->getInverseMass() * correction);
                }

                /*std::cout << "[FIX] newP1=" << currentCollision.first->getPosition() << ", dims=" << currentCollision.first->asArea().getWidth() << "x" << currentCollision.first->asArea().getHeight() << ")" << std::endl;
                std::cout << "[FIX] newP2=" << currentCollision.second->getPosition() << ", dims=" << currentCollision.second->asArea().getWidth() << "x" << currentCollision.second->asArea().getHeight() << ")" << std::endl;
                std::cout << "------" << std::endl;*/
            }
        }

        utils::Vector2d CollisionsSolver::computeCollisionNormal(const PotentialCollision& collision) const
        {
            return -(collision.second->getLinearSpeed() - collision.first->getLinearSpeed()).normalized();
        }

        utils::Vector2d CollisionsSolver::computePenetrationDepth(const PotentialCollision& collision) const
        {
            // Convenience manipulation variable for objects.
            const RigidBody& lhs(*collision.first);
            const RigidBody& rhs(*collision.second);
            // Compute relative velocity.
            utils::Vector2d relativeVelocity(lhs.getLinearSpeed() - rhs.getLinearSpeed());

            // So to compute the penetration depth, we should find the maximum distance by which the first object of the input collision
            // has penetrated the second one.
            // To do so, let's first build the list of points which should be considered: basically if the general moving direction of the
            // first object is up, we should only consider the top edge of the box.
            // So, start by creating an empty line of points to consider.
            std::vector<utils::Vector2d> pointsToConsider;
            // Then, add points according to the relative velocity
            const int alongX(relativeVelocity.x() > 0.0 ? 1 : (relativeVelocity.x() < 0.0 ? -1 : 0));
            const int alongY(relativeVelocity.y() > 0.0 ? 1 : (relativeVelocity.y() < 0.0 ? -1 : 0));
            if (alongX > 0)
            {
                pointsToConsider.push_back(lhs.asArea().getTopRightCorner());
                pointsToConsider.push_back(lhs.asArea().getBottomRightCorner());
                if (alongY > 0)
                {
                    pointsToConsider.push_back(lhs.asArea().getTopLeftCorner());
                }
                else if (alongY < 0)
                {
                    pointsToConsider.push_back(lhs.asArea().getBottomLeftCorner());
                }
            }
            else if (alongX < 0)
            {
                pointsToConsider.push_back(lhs.asArea().getTopLeftCorner());
                pointsToConsider.push_back(lhs.asArea().getBottomLeftCorner());
                if (alongY > 0)
                {
                    pointsToConsider.push_back(lhs.asArea().getTopRightCorner());
                }
                else if (alongY < 0)
                {
                    pointsToConsider.push_back(lhs.asArea().getBottomRightCorner());
                }
            }
            else
            {
                if (alongY > 0)
                {
                    pointsToConsider.push_back(lhs.asArea().getTopLeftCorner());
                    pointsToConsider.push_back(lhs.asArea().getTopRightCorner());
                }
                else if (alongY < 0)
                {
                    pointsToConsider.push_back(lhs.asArea().getBottomLeftCorner());
                    pointsToConsider.push_back(lhs.asArea().getBottomRightCorner());
                }
                else
                {
                    // Null velocity collision.. hmm...
                    std::cerr << "[ERROR] Could not compute penetration depth with collision speed " << relativeVelocity << std::endl;
                    return utils::Vector2d();
                }
            }
            // Filter points based on whether they are inside the intersected object's box and compute the closest point.
            using CollectionOfPairs = std::vector<std::pair<utils::Vector2d, utils::Vector2d>>;
            CollectionOfPairs closestPoints;
            int currentIndex(pointsToConsider.size() - 1);
            while (currentIndex >= 0)
            {
                // Check whether this point belongs to the other object's box.
                if (!rhs.asArea().isInside(pointsToConsider[currentIndex]))
                {
                    // Remove this point.
                    pointsToConsider.erase(pointsToConsider.begin() + currentIndex);
                }
                else
                {
                    closestPoints.push_back(std::make_pair(pointsToConsider[currentIndex], rhs.asArea().getNearestPointAlongDirection(pointsToConsider[currentIndex], relativeVelocity)));
                }
                --currentIndex;
            }
            // Check whether some points are still in the list.
            if (closestPoints.empty())
            {
                // We may be in a case of a large object as lhs is intersecting a small object as rhs. Let's try to compute the reverse collision
                // and invert the result.
                return computePenetrationDepth(std::make_pair(collision.second, collision.first));
            }
            // Now compute the mean penetration depth.
            utils::Vector2d penetrationDepth;
            for (CollectionOfPairs::const_iterator collisionPair = closestPoints.cbegin() ; collisionPair != closestPoints.cend() ; ++collisionPair)
            {
                //std::cout << "[DEPTH] p=" << collisionPair->first << ", closest=" << collisionPair->second << std::endl;

                penetrationDepth += ((collisionPair->first - collisionPair->second) / closestPoints.size());
            }
            // Return the compute penetration depth.
            return penetrationDepth;
        }

        double CollisionsSolver::computeCollisionImpulse(const PotentialCollision& collision, const utils::Vector2d& normal) const
        {
            // Convenience manipulation variable for objects.
            const RigidBody& lhs(*collision.first);
            const RigidBody& rhs(*collision.second);

            // Compute the relative velocity of collided objects.
            utils::Vector2d relativeVelocity(rhs.getLinearSpeed() - lhs.getLinearSpeed());
            // Project this speed along the collision normal.
            const double velocityAlongNormal(relativeVelocity * normal);
            // Do not resolve if objects are already separating.
            if (velocityAlongNormal > 0.0)
            {
                return 0.0;
            }
            // Compute the restitution for this impulse.
            const double collisionRestitution(std::min(lhs.getElasticity(), rhs.getElasticity()));
            // Compute the impulse magnitude.
            double impulseMagnitude(-(1.0 + collisionRestitution) * velocityAlongNormal);
            impulseMagnitude /= (lhs.getInverseMass() + rhs.getInverseMass());
            // Return the built-in impulse magnitude.
            return impulseMagnitude;
        }
    }
}
