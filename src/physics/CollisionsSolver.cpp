
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

                // We need to compute two information: the collision normal and the penetration depth (i.e. how far both objects have inter-penetrated).
                const utils::Vector2d collisionNormal(computeCollisionNormal(currentCollision));
                const utils::Vector2d penetrationDepth(computePenetrationDepth(currentCollision));

                // Compute the impulse based on both colliding objects' properties and the above properties.
                const double impulseMagnitude(computeCollisionImpulse(currentCollision, collisionNormal));
                // Deduce the impulse vector from this impulse and the collision's normal.
                utils::Vector2d impulse(impulseMagnitude * collisionNormal);
                // Now we can modify the speed of each rigid body accordingly.
                // We know that the normal is computed so that currentCollision.first is moving in the direction of the normal.

                currentCollision.first->linearMove(-currentCollision.first->getInverseMass() * impulse);
                currentCollision.second->linearMove(currentCollision.second->getInverseMass() * impulse);

                const double percent(0.2);
                const double slop(0.01);
                const utils::Vector2d correction(std::max(penetrationDepth.length() - slop, 0.0) * percent * collisionNormal / (currentCollision.first->getInverseMass() + currentCollision.second->getInverseMass()));

                std::cout << "------" << std::endl;
                std::cout << "[FIX] Solving collision between obj1=" << currentCollision.first->getMass() << " and obj2=" << currentCollision.second->getMass() << std::endl;
                std::cout << "[FIX] v1=" << currentCollision.first->getLinearSpeed() << ", v2=" << currentCollision.second->getLinearSpeed() << std::endl;
                std::cout << "[FIX] p1=" << currentCollision.first->getPosition() << ", p2=" << currentCollision.second->getPosition() << std::endl;
                std::cout << "[FIX] n=" << collisionNormal << " (old=" << (currentCollision.second->getPosition() - currentCollision.first->getPosition()).normalized() << "), impulse=" << impulseMagnitude << ", (vec=" << impulse << ")" << std::endl;
                std::cout << "[FIX] obj1=" << (-1.0 / currentCollision.first->getMass()) * impulse << ", obj2=" << (1.0 / currentCollision.second->getMass()) * impulse << ", m1=" << currentCollision.first->getMass() << ", m2=" << currentCollision.second->getMass() << std::endl;
                std::cout << "[FIX] correction is " << correction << " (penetration=" << penetrationDepth << ")" << std::endl;

                currentCollision.first->translate(-currentCollision.first->getInverseMass() * correction);
                currentCollision.second->translate(currentCollision.second->getInverseMass() * correction);

                std::cout << "[FIX] newP1=" << currentCollision.first->getPosition() << ", newP2=" << currentCollision.second->getPosition() << " (d1=" << currentCollision.first->asArea().getWidth() << "x" << currentCollision.first->asArea().getHeight() << ", d2=" << currentCollision.second->asArea().getWidth() << "x" << currentCollision.second->asArea().getHeight() << ")" << std::endl;
                std::cout << "------" << std::endl;
            }
        }

        utils::Vector2d CollisionsSolver::computeCollisionNormal(const PotentialCollision& collision) const
        {
            return -(collision.second->getLinearSpeed() - collision.first->getLinearSpeed()).normalized();
        }

        utils::Vector2d CollisionsSolver::computePenetrationDepth(const PotentialCollision& collision) const
        {
            const utils::Vector2d distanceCenterToCenter(collision.first->getPosition() - collision.second->getPosition());
            const utils::Vector2d dimensions(collision.first->asArea().getWidth() / 2.0 + collision.second->asArea().getWidth() / 2.0,
                                             collision.first->asArea().getHeight() / 2.0 + collision.second->asArea().getHeight() / 2.0);
            return utils::Vector2d(std::abs(std::max(0.0, dimensions.x() - distanceCenterToCenter.x())),
                                   std::abs(std::max(0.0, dimensions.y() - distanceCenterToCenter.y())));
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
