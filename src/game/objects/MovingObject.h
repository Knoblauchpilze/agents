#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "Vector3d.h"
#include "RigidBodyListener.h"
#include "EnvironmentalObject.h"

namespace environment
{
    namespace objects
    {
        class MovingObject: public EnvironmentalObject, public physics::RigidBodyListener
        {
            public:

                MovingObject(const double& x,
                             const double& y,
                             const double& width,
                             const double& height,
                             const double& density,
                             const double& elasticity);

                virtual ~MovingObject();

                virtual void onRigidBodyUpdated();

                void applyForce(utils::Vector2d& force);

                const utils::Vector2d& getLinearAcceleration() const;

                const utils::Vector2d& getLinearSpeed() const;

            protected:

                virtual void clampLinearForce(utils::Vector2d& force) const;

            private:
        };
    }
}

#endif // MOVINGOBJECT_H
