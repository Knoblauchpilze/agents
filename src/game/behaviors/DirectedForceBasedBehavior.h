#ifndef DIRECTEDFORCEBASEDBEHAVIOR_H
#define DIRECTEDFORCEBASEDBEHAVIOR_H

#include "DirectedMotionBehavior.h"
#include "RandomPositionGenerator.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class DirectedForceBasedBehavior: public DirectedMotionBehavior
            {
                public:

                    DirectedForceBasedBehavior(const utils::Vector2d& position, const utils::sdl::Area& wanderingArea);

                    virtual ~DirectedForceBasedBehavior();

                    virtual
                    std::vector<environment::agents::influences::InfluenceShPtr>
                    perform(const std::vector<environment::perceptions::Perception>& perceptions);

                protected:

                    virtual void pickNewTarget();

                    utils::Vector2d computeAvoidanceVector(const VectorOfPerceptions& perceptions) const;

                    virtual double computeRepulsionForce(const utils::Vector2d& current, const utils::Vector2d& other) const;

                private:

                    std::mt19937_64 m_rng;
                    utils::random::RandomPositionGenerator m_wanderingArea;
            };
        }
    }
}

#endif // DIRECTEDFORCEBASEDBEHAVIOR_H
