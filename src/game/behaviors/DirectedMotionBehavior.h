#ifndef DIRECTEDMOTIONBEHAVIOR_H
#define DIRECTEDMOTIONBEHAVIOR_H

#include "Vector2d.h"
#include "MotionBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class DirectedMotionBehavior: public MotionBehavior
            {
                public:

                    DirectedMotionBehavior(const utils::Vector2d& position, const double& distanceToArrival);

                    virtual ~DirectedMotionBehavior();

                    virtual bool isComplete() const;

                    virtual
                    std::vector<environment::agents::influences::InfluenceShPtr>
                    perform(const std::vector<environment::perceptions::Perception>& perceptions);

                protected:

                    const double& getDistanceToArrival() const;

                    bool arrivedToTarget() const;

                    double computeDistanceToTarget() const;

                    virtual bool hasTarget() const = 0;

                    virtual const utils::Vector2d& getTarget() const = 0;

                    virtual void setTarget(const utils::Vector2d& target) const = 0;

                    virtual void pickNewTarget() = 0;

                    virtual utils::Vector2d computeMotionForceToTarget() const = 0;

                private:

                    double m_distanceToArrival;
            };
        }
    }
}

#endif // DIRECTEDMOTIONBEHAVIOR_H
