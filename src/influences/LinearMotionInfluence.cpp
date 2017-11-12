
#include "LinearMotionInfluence.h"

namespace environment
{
	namespace agents
	{
		namespace influences
		{
			LinearMotionInfluence::LinearMotionInfluence(const utils::Vector2d& force):
			    Influence(),
			    m_force(force)
            {
                // Nothing to do.
            }

			LinearMotionInfluence::~LinearMotionInfluence()
			{
				// Nothing to do.
			}

			void LinearMotionInfluence::apply()
			{
				if (valid())
                {
                    getReceiver().applyForce(m_force);
				}
			}
		}
	}
}
