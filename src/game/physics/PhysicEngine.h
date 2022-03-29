#ifndef PHYSICENGINE_H
#define PHYSICENGINE_H

#include <vector>
#include "RigidBody.h"
#include "TimeManager.h"
#include "CollisionsSolver.h"

namespace environment
{
    namespace physics
    {
        class PhysicEngine
        {
            public:

                PhysicEngine();

                virtual ~PhysicEngine();

                void registerBody(RigidBodyShPtr body);

                void removeBody(RigidBodyShPtr body);

                void simulate(const environment::time::TimeManager& manager);

            private:

                void applyForces(const environment::time::TimeManager& manager);

            private:

                std::vector<RigidBodyShPtr> m_bodies;
                CollisionsSolver m_collisionsSolver;

        };
    }
}

#endif // PHYSICENGINE_H
