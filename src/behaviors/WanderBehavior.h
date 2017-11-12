#ifndef WANDERBEHAVIOR_H
#define WANDERBEHAVIOR_H

#include "Area.h"
#include "DirectedMotionBehavior.h"
#include "RandomPositionGenerator.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class WanderBehavior: public DirectedMotionBehavior
            {
                public:

                    WanderBehavior(const utils::Vector2d& position,
                                   const utils::sdl::Area& wanderingArea,
                                   const double& desiredSpeed,
                                   const double& distanceToDeccelerate);

                    virtual ~WanderBehavior();

                    virtual bool isComplete() const;

                protected:

                    virtual bool hasTarget() const;

                    virtual const utils::Vector2d& getTarget() const;

                    virtual void pickNewTarget();

                    virtual utils::Vector2d computeMotionForceToTarget() const;

                private:

                    static const double sk_speedCorrectionTime;

                    utils::random::RandomPositionGenerator m_random;

                    bool m_hasTarget;
                    utils::Vector2d m_target;

                    double m_distanceToDeccelerate;
                    double m_desiredSpeed;
            };
        }
    }
}

#endif // WANDERBEHAVIOR_H
