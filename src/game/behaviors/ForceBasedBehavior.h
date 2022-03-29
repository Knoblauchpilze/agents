#ifndef FORCEBASEDBEHAVIOR_H
#define FORCEBASEDBEHAVIOR_H

#include "MotionBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class ForceBasedBehavior: public MotionBehavior
            {
                public:

                    ForceBasedBehavior(const utils::Vector2d& position);

                    virtual ~ForceBasedBehavior();

                    virtual
                    std::vector<std::shared_ptr<environment::agents::influences::Influence>>
                    perform(const VectorOfPerceptions& perceptions);

                protected:

                    utils::Vector2d computeAvoidanceVector(const VectorOfPerceptions& perceptions) const;

                    virtual double computeRepulsionForce(const utils::Vector2d& current, const utils::Vector2d& other) const;
            };
        }
    }
}

#endif // FORCEBASEDBEHAVIOR_H
