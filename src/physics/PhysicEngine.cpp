
#include <algorithm>
#include "PhysicEngine.h"

namespace environment
{
    namespace physics
    {
        PhysicEngine::PhysicEngine():
            m_bodies(),
            m_collisionsSolver()
        {
            // Nothing to do.
        }

        PhysicEngine::~PhysicEngine()
        {
            // Nothing to do.
        }

        void PhysicEngine::registerBody(const RigidBodyShPtr body)
        {
            m_bodies.push_back(body);
        }

        void PhysicEngine::removeBody(const RigidBodyShPtr body)
        {
            std::vector<RigidBodyShPtr>::iterator bodyToRemove(m_bodies.begin());
            while (bodyToRemove != m_bodies.end() && *bodyToRemove != body)
            {
                ++bodyToRemove;
            }
            if (bodyToRemove != m_bodies.end())
            {
                m_bodies.erase(bodyToRemove);
            }
        }

        void PhysicEngine::simulate(const environment::time::TimeManager& manager)
        {
            /*std::cout << "*****" << std::endl;
            std::cout << "[PHYSIC] Applying forces" << std::endl;*/
            // Apply forces to objects.
            applyForces(manager);
            //std::cout << "[PHYSIC] Solving collisions" << std::endl;
            // Solve collisions.
            m_collisionsSolver.solve(m_bodies);
            //std::cout << "*****" << std::endl;
        }

        //===========

        void PhysicEngine::applyForces(const environment::time::TimeManager& manager)
        {
            // Traverse each rigid body.
            for (std::vector<RigidBodyShPtr>::iterator rigidBody = m_bodies.begin() ; rigidBody != m_bodies.end() ; ++rigidBody)
            {
                (*rigidBody)->applyTimeDelta(manager);
            }
        }
    }
}
