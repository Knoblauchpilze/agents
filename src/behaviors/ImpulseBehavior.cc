
#include "ImpulseBehavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            const double ImpulseBehavior::sk_speedNotAlongImpulseThreshold(0.001);

            ImpulseBehavior::ImpulseBehavior(const utils::Vector2d& position, const utils::Vector2d& impulse, bool repetitive, const double& maxForce):
                MotionBehavior(position, maxForce),
                m_repetitive(repetitive),
                m_impulseGiven(false),
                m_impulse(impulse)
            {
                // Nothing to do.
            }

            ImpulseBehavior::~ImpulseBehavior()
            {
                // Nothing to do.
            }

            bool ImpulseBehavior::isComplete() const
            {
                return (m_impulseGiven && !m_repetitive);
            }

            std::vector<std::shared_ptr<environment::agents::influences::Influence>>
            ImpulseBehavior::perform(const VectorOfPerceptions&)
            {
                // Check whether we should give an impulse.
                if (needToImpulse())
                {
                    m_impulseGiven = true;
                    std::cout << "[IMPULSE]" << std::endl;
                    // Create the output vector of influences and return it.
                    return std::vector<environment::agents::influences::InfluenceShPtr>(1u, createFromVector(m_impulse));
                }
                // No influence for this behaviour.
                return std::vector<environment::agents::influences::InfluenceShPtr>();
            }

            //======

            bool ImpulseBehavior::needToImpulse() const
            {
                return (!m_impulseGiven || getSpeed() * m_impulse <= sk_speedNotAlongImpulseThreshold);
            }
        }
    }
}
