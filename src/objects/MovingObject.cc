
#include "Vector2d.h"
#include "MovingObject.h"
#include "ComparisonUtils.h"

namespace environment
{
    namespace objects
    {
        MovingObject::MovingObject(const double& x,
                                   const double& y,
                                   const double& width,
                                   const double& height,
                                   const double& density,
                                   const double& elasticity):
            EnvironmentalObject(x, y, width, height, density, elasticity)
        {
            // Register as a listener of this rigid body.
            getRigidBody()->addListener(this);
        }

        MovingObject::~MovingObject()
        {
            // Nothing to do.
        }

        void MovingObject::onRigidBodyUpdated()
        {
		    getBoundingBox().setPosition(getRigidBody()->getPosition());
		    fireObjectModification();
        }

		void MovingObject::applyForce(utils::Vector2d& force)
		{
		    clampLinearForce(force);
		    getRigidBody()->applyForce(force);
		}

		const utils::Vector2d& MovingObject::getLinearAcceleration() const
		{
		    return getRigidBody()->getLinearAcceleration();
		}

        const utils::Vector2d& MovingObject::getLinearSpeed() const
        {
            return getRigidBody()->getLinearSpeed();
        }

        //==========

        void MovingObject::clampLinearForce(utils::Vector2d&) const
        {
            // Do nothing.
        }
    }
}
