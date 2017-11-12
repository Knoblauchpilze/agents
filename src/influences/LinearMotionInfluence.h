#ifndef LINEARMOTIONINFLUENCE_H
#define LINEARMOTIONINFLUENCE_H

#include "Vector2d.h"
#include "Influence.h"

namespace environment
{
	namespace agents
	{
		namespace influences
		{
			class LinearMotionInfluence: public Influence
			{
			    public:

			        LinearMotionInfluence(const utils::Vector2d& force);

                    virtual ~LinearMotionInfluence();

                    virtual void apply();

                private:

                    utils::Vector2d m_force;
			};
		}
	}
}

#endif // LINEARMOTIONINFLUENCE_H
