#ifndef COLLISIONSOLVER_H
#define COLLISIONSOLVER_H

#include <vector>
#include <memory>
#include "RigidBody.h"
#include "BoundingBox.h"

namespace environment
{
    namespace physics
    {
        class CollisionsSolver
        {
            public:

                CollisionsSolver();

                virtual ~CollisionsSolver();

                void solve(const std::vector<RigidBodyShPtr>& bodies);

            private:

                using PotentialCollision = std::pair<RigidBodyShPtr, RigidBodyShPtr>;

                void collisionsDetection(const std::vector<RigidBodyShPtr>& bodies, std::vector<PotentialCollision>& collisions) const;

                void sortAndFilterCollisions(std::vector<PotentialCollision>& collisions) const;

                void solveCollisions(const std::vector<PotentialCollision>& collisions) const;

                utils::Vector2d computeCollisionNormal(const PotentialCollision& collision) const;

                utils::Vector2d computePenetrationDepth(const PotentialCollision& collision) const;

                double computeCollisionImpulse(const PotentialCollision& collision, const utils::Vector2d& normal) const;

            private:
        };
    }
}

#endif // COLLISIONSOLVER_H
