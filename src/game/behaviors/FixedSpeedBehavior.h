#ifndef FIXEDSPEEDBEHAVIOR_H
#define FIXEDSPEEDBEHAVIOR_H

#include "Vector2d.h"
#include "MotionBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class FixedSpeedBehavior: public MotionBehavior
            {
                public:

                    FixedSpeedBehavior(const utils::Vector2d& position,
                                       const utils::Vector2d& desiredSpeed,
                                       const double& timeInterval);

                    virtual ~FixedSpeedBehavior();

                    virtual bool isComplete() const;

                    virtual
                    std::vector<environment::agents::influences::InfluenceShPtr>
                    perform(const std::vector<environment::perceptions::Perception>& perceptions);

                protected:

                    bool reachedDesiredSpeed() const;

                    utils::Vector2d accelerateToSpeed(const utils::Vector2d& desired, const double& secondsToReachSpeed) const;

                private:

                    double m_timeInterval;
                    utils::Vector2d m_desiredSpeed;
                    double m_speedTolerance;
            };
        }
    }
}

#endif // FIXEDSPEEDBEHAVIOR_H
