
#include "Agent.h"
#include "Area.h"
#include "LinearMotionInfluence.h"
#include "MotionBehavior.h"

#include "ImpulseBehavior.h"
#include "FixedSpeedBehavior.h"
#include "WanderBehavior.h"

namespace environment
{
    namespace agents
    {
        unsigned int count(0);

        Agent::Agent(Animat& animat):
            m_animat(animat),
            m_motionBehaviors()
        {
            // Nothing to do.
        }

        Agent::~Agent()
        {
            // Nothing to do.
        }

        void Agent::live()
        {
            // Check whether some behaviours are available.
            if (m_motionBehaviors.empty())
            {
                takeDecisions();
            }
            // Perform each behaviour.
            using BehaviorShPtrVector = std::vector<std::shared_ptr<agents::behaviors::MotionBehavior>>;
            using InfluenceShPtrVector = std::vector<agents::influences::InfluenceShPtr>;
            BehaviorShPtrVector remainingBehaviors;
            for (BehaviorShPtrVector ::iterator behavior = m_motionBehaviors.begin() ; behavior != m_motionBehaviors.end() ; ++behavior)
            {
                // Update this behaviour.
                (*behavior)->setPosition(getPosition());
                (*behavior)->setSpeed(getLinearSpeed());
                // Perform this behaviour.
                InfluenceShPtrVector influences((*behavior)->perform(getPerceptions()));
                collectInfluences(influences);
                // Remove this behaviour if needed.
                if (!(*behavior)->isComplete())
                {
                    remainingBehaviors.push_back(*behavior);
                }
            }
            m_motionBehaviors.swap(remainingBehaviors);
        }

        //==============

        void Agent::takeDecisions()
        {
            if (count > 0)
            {
                return;
            }
            ++count;

            std::shared_ptr<agents::behaviors::MotionBehavior> behavior(nullptr);
            behavior = std::make_shared<agents::behaviors::FixedSpeedBehavior>(getPosition(), utils::Vector2d(1.0, 0.0), 5.0);

            m_motionBehaviors.push_back(behavior);
        }

        void Agent::collectInfluences(const std::vector<influences::InfluenceShPtr>& influences)
        {
            for (std::vector<influences::InfluenceShPtr>::const_iterator influence = influences.cbegin() ; influence != influences.cend() ; ++influence)
            {
                m_animat.collectInfluence(*influence);
            }
        }

        const std::vector<environment::perceptions::Perception>& Agent::getPerceptions() const
        {
            return m_animat.getPerceptions();
        }

        utils::Vector2d Agent::getPosition() const
        {
            const utils::sdl::Area& thisBoundingBox(m_animat.getBoundingBox().asArea());
            return utils::Vector2d(thisBoundingBox.getX(), thisBoundingBox.getY());
        }

        utils::Vector2d Agent::getLinearSpeed() const
        {
            return m_animat.getLinearSpeed();
        }

        utils::Vector2d Agent::getLinearAcceleration() const
        {
            return m_animat.getLinearAcceleration();
        }
    }
}
