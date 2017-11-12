#ifndef IMPULSEBEHAVIOR_H
#define IMPULSEBEHAVIOR_H

#include "Vector2d.h"
#include "MotionBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class ImpulseBehavior: public MotionBehavior
            {
                public:

                    ImpulseBehavior(const utils::Vector2d& position,
                                    const utils::Vector2d& impulse,
                                    bool repetitive,
                                    const double& maxForce = 1.0);

                    virtual ~ImpulseBehavior();

                    virtual bool isComplete() const;

                    virtual
                    std::vector<std::shared_ptr<environment::agents::influences::Influence>>
                    perform(const VectorOfPerceptions& perceptions);

                private:

                    bool needToImpulse() const;

                private:

                    static const double sk_speedNotAlongImpulseThreshold;

                    bool m_repetitive;

                    bool m_impulseGiven;
                    utils::Vector2d m_impulse;
            };
        }
    }
}

#endif // IMPULSEBEHAVIOR_H
