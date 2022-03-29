#ifndef BODY_H
#define BODY_H

#include <memory>
#include "MovingObject.h"
#include "Frustum.h"
#include "Influence.h"
#include "Perception.h"

namespace environment
{
    namespace agents
    {
        namespace influences
        {
            class Influence;
        }
    }

    namespace objects
    {
        class Body: public environment::objects::MovingObject
        {
            public:

                Body(const double& x,
                     const double& y,
                     const double& width,
                     const double& height,
                     const double& density,
                     const double& elasticity);

                virtual ~Body();

                const frustum::Frustum& getFrustum() const;

                virtual void influence(const std::shared_ptr<agents::influences::Influence> influence);

                std::vector<std::shared_ptr<agents::influences::Influence>> consumeInfluences();

                void onPerceptionsComputed(const std::vector<environment::perceptions::Perception>& perceptions);

                const std::vector<environment::perceptions::Perception>& getPerceptions() const;

                virtual void onRigidBodyUpdated();

            protected:

                virtual void clampLinearForce(utils::Vector2d& force) const override;

            private:

                void assignFrustum();

            private:

                static const double sk_bodyToFrustumRatio;
                static const double sk_forceClampThreshold;

                frustum::FrustumShPtr m_frustum;
                std::vector<std::shared_ptr<agents::influences::Influence>> m_influences;
                std::vector<environment::perceptions::Perception> m_perceptions;

        };

        using BodyShPtr = std::shared_ptr<Body>;
    }
}

#endif // BODY_H
