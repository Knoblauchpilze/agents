#ifndef MOTIONBEHAVIOR_H
#define MOTIONBEHAVIOR_H

#include "Vector2d.h"
#include "Behavior.h"
#include "Influence.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {

            class MotionBehavior: public Behavior
            {
                public:

                    MotionBehavior(const utils::Vector2d& position, const double& maxForce = 1.0);

                    virtual ~MotionBehavior();

                    void setPosition(const utils::Vector2d& position);

                    void setSpeed(const utils::Vector2d& speed);

                protected:

                    const utils::Vector2d& getPosition() const;

                    const utils::Vector2d& getSpeed() const;

                    const double& getMaxForce() const;

                    bool isMoving(const double& threshold) const;

                    std::shared_ptr<environment::agents::influences::Influence> createFromVector(utils::Vector2d& force) const;

                private:

                    utils::Vector2d m_position;
                    utils::Vector2d m_speed;
                    double m_maxForce;
            };
        }
    }
}

#endif // MOTIONBEHAVIOR_H
