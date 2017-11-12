#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <vector>
#include <memory>
#include "Area.h"
#include "Vector2d.h"
#include "RigidBodyListener.h"
#include "TimeManager.h"

namespace environment
{
    namespace physics
    {
        class RigidBody
        {
            public:

                RigidBody(const utils::sdl::Area& body, const double& density, const double& elasticity);

                ~RigidBody();

                void addListener(RigidBodyListener* listener);

                inline bool isInfinitelyMassive() const;

                inline const double& getMass() const;

                inline double getInverseMass() const;

                inline const double& getElasticity() const;

                inline const utils::Vector2d& getLinearSpeed() const;

                inline const utils::Vector2d& getLinearAcceleration() const;

                inline utils::Vector2d getPosition() const;

                inline bool intersects(const RigidBody& other) const;

                inline void applyForce(const utils::Vector2d& force);

                inline void linearMove(const utils::Vector2d& speed);

                inline void translate(const utils::Vector2d& translation);

                inline const utils::sdl::Area& asArea() const;

                void applyTimeDelta(const time::TimeManager& manager);

            private:

                void setup();

                void fireRigidBodyModification();

            private:

                utils::sdl::Area m_area;
                double m_density;
                double m_mass;

                double m_elasticity;

                utils::Vector2d m_force;

                utils::Vector2d m_linearSpeed;
                utils::Vector2d m_linearAcceleration;

                std::vector<RigidBodyListener*> m_listeners;

            public:
                unsigned int m_rb;
        };

        using RigidBodyShPtr = std::shared_ptr<RigidBody>;
    }
}

#include "RigidBody.hxx"

#endif // RIGIDBODY_H
