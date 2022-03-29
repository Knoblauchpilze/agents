#ifndef ANIMAT_H
#define ANIMAT_H

#include <memory>
#include "Agent.h"
#include "Body.h"
#include "Influence.h"
#include "Perception.h"

namespace environment
{
    namespace objects
    {
		class Body;
    }

	namespace agents
	{
		class Agent;

		namespace influences
		{
		    class Influence;
		}

		class Animat {

            public:

                Animat(const double& x, const double& y, const double& density, const double& elasticity);

                virtual ~Animat();

                std::shared_ptr<agents::Agent> spawnAgent();

                std::shared_ptr<objects::Body> spawnBody();

                virtual void collectInfluence(const std::shared_ptr<influences::Influence>& influence);

                const std::vector<environment::perceptions::Perception>& getPerceptions() const;

                const environment::box::BoundingBox& getBoundingBox() const;

                const utils::Vector2d& getLinearAcceleration() const;

                const utils::Vector2d& getLinearSpeed() const;

            protected:

                virtual std::shared_ptr<agents::Agent> createAgent();

                virtual std::shared_ptr<objects::Body> createBody() const;

            private:

                static const double sk_defaultBodiesDimensions;

                double m_x;
                double m_y;

                double m_density;
                double m_elasticity;

                std::shared_ptr<agents::Agent> m_agent;
                std::shared_ptr<objects::Body> m_body;
		};

        using AnimatShPtr = std::shared_ptr<Animat>;
    }
}

#endif // ANIMAT_H
