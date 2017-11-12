
#include "Body.h"
#include "RectangleFrustum.h"

namespace environment
{
    namespace objects
    {
        const double Body::sk_bodyToFrustumRatio(1.32);
        const double Body::sk_forceClampThreshold(1.0);

        Body::Body(const double& x,
                   const double& y,
                   const double& width,
                   const double& height,
                   const double& density,
                   const double& elasticity):
            environment::objects::MovingObject(x, y, width, height, density, elasticity),
            m_frustum()
        {
            // Assign frustum
            assignFrustum();
        }

        Body::~Body()
        {
            // Nothing to do.
        }

        const frustum::Frustum& Body::getFrustum() const
        {
            return *m_frustum;
        }

        void Body::influence(const agents::influences::InfluenceShPtr influence)
        {
			// Insert this influence into the internal set
			m_influences.push_back(influence);
		}

		std::vector<environment::agents::influences::InfluenceShPtr> Body::consumeInfluences()
		{
			// Create the output vector
			std::vector<std::shared_ptr<environment::agents::influences::Influence>> outputInfluencesList;
			// Swap the internal influences list
			outputInfluencesList.swap(m_influences);
			// Return the output vector
			return outputInfluencesList;
		}

		void Body::onPerceptionsComputed(const std::vector<environment::perceptions::Perception>& perceptions)
		{
		    m_perceptions.clear();
			m_perceptions.insert(std::end(m_perceptions), std::begin(perceptions), std::end(perceptions));
		}

		const std::vector<environment::perceptions::Perception>& Body::getPerceptions() const
		{
		    return m_perceptions;
		}

		void Body::onRigidBodyUpdated()
		{
		    m_frustum->setPosition(getRigidBody()->getPosition());
		    MovingObject::onRigidBodyUpdated();
		}

        //=============

        void Body::clampLinearForce(utils::Vector2d& force) const
        {
            if (std::abs(force.x()) > sk_forceClampThreshold) {
                force.setX(std::copysign(sk_forceClampThreshold, force.x()));
            }
            if (std::abs(force.y()) > sk_forceClampThreshold) {
                force.setY(std::copysign(sk_forceClampThreshold, force.y()));
            }
        }

        //=============

        void Body::assignFrustum()
        {
            const utils::sdl::Area& area(getBoundingBox().asArea());
            const double frustumX(area.getX());
            const double frustumY(area.getY());
            const double frustumWidth(area.getWidth() * sk_bodyToFrustumRatio);
            const double frustumHeight(area.getHeight() * sk_bodyToFrustumRatio);
            m_frustum = std::make_shared<frustum::RectangleFrustum>(utils::sdl::Area(frustumX, frustumY, frustumWidth, frustumHeight));
        }
    }
}
