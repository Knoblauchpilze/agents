#ifndef DIRECTEDFIXEDSPEEDBEHAVIOR_H
#define DIRECTEDFIXEDSPEEDBEHAVIOR_H

#include "Area.h"
#include "Vector2d.h"
#include "DirectedMotionBehavior.h"
#include "RandomPositionGenerator.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class DirectedFixedSpeedBehavior: public DirectedMotionBehavior
            {
                public:

                    DirectedFixedSpeedBehavior(const utils::Vector2d& position,
                                               const utils::sdl::Area& wanderingArea,
                                               const utils::Vector2d& desiredSpeed,
                                               const double& timeInterval);

                    virtual ~DirectedFixedSpeedBehavior();

                    virtual
                    std::vector<environment::agents::influences::InfluenceShPtr>
                    perform(const std::vector<environment::perceptions::Perception>& perceptions);

                protected:

                    bool reachedDesiredSpeed() const;

                    utils::Vector2d moveToTarget(const utils::Vector2d& target, const double& secondsToReachTarget) const;

                    utils::Vector2d accelerateToSpeed(const utils::Vector2d& desired, const double& secondsToReachSpeed) const;

                    virtual void pickNewTarget();

                private:

                    double m_timeInterval;
                    utils::Vector2d m_desiredSpeed;
                    double m_speedTolerance;
                    utils::random::RandomPositionGenerator m_targetPicker;
            };
        }
    }
}

#endif // DIRECTEDFIXEDSPEEDBEHAVIOR_H
