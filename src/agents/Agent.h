#ifndef AGENT_H
#define AGENT_H

#include <memory>
#include "Animat.h"
#include "Vector3d.h"
#include "Perception.h"

namespace environment
{
    namespace agents
    {
        class Animat;

        namespace influences
        {
            class Influence;
        }

        namespace behaviors
        {
            class MotionBehavior;
        }

        class Agent
        {
            public:

                Agent(Animat& animat);

                virtual ~Agent();

                virtual void live();

            protected:

                virtual void takeDecisions();

                void collectInfluences(const std::vector<std::shared_ptr<influences::Influence>>& influences);

                const std::vector<environment::perceptions::Perception>& getPerceptions() const;

                utils::Vector2d getPosition() const;

                utils::Vector2d getLinearSpeed() const;

                utils::Vector2d getLinearAcceleration() const;

            private:

                Animat& m_animat;
                std::vector<std::shared_ptr<agents::behaviors::MotionBehavior>> m_motionBehaviors;
        };

        using AgentShPtr = std::shared_ptr<Agent>;
    }
}

#endif // AGENT_H
