
#include "Animat.h"

namespace environment
{
	namespace agents
	{
	    const double Animat::sk_defaultBodiesDimensions(1.0);

		Animat::Animat(const double& x, const double& y, const double& density, const double& elasticity) :
			m_x(x),
			m_y(y),
			m_density(density),
			m_elasticity(elasticity),
			m_agent(nullptr),
			m_body(nullptr)
		{
			// Nothing to do.
		}

		Animat::~Animat()
		{
			// Nothing to do.
		}

		agents::AgentShPtr Animat::spawnAgent()
		{
		    if (m_agent == nullptr)
            {
				m_agent = createAgent();
			}
			return m_agent;
		}

		objects::BodyShPtr Animat::spawnBody()
		{
			if (m_body == nullptr)
            {
				m_body = createBody();
			}
			return m_body;
		}

		void Animat::collectInfluence(const std::shared_ptr<influences::Influence>& influence)
		{
		    // Force properties of this influence to match the animat's internal properties
			influence->setEmitter(m_agent);
			influence->setReceiver(m_body);
			// Influence the body with this built-in influence
			if (m_body != nullptr) {
				m_body->influence(influence);
			}
		}

		const std::vector<environment::perceptions::Perception>& Animat::getPerceptions() const
		{
		    return m_body->getPerceptions();
		}

		const environment::box::BoundingBox& Animat::getBoundingBox() const
		{
		    const objects::Body& body(*m_body);
		    return body.getBoundingBox();
		}

		const utils::Vector2d& Animat::getLinearAcceleration() const
		{
		    return m_body->getLinearAcceleration();
		}

        const utils::Vector2d& Animat::getLinearSpeed() const
        {
            return m_body->getLinearSpeed();
        }

		//=============

		agents::AgentShPtr Animat::createAgent()
		{
		    return std::make_shared<Agent>(*this);
		}

        objects::BodyShPtr Animat::createBody() const
        {
            return std::make_shared<objects::Body>(m_x, m_y, sk_defaultBodiesDimensions, sk_defaultBodiesDimensions, m_density, m_elasticity);
        }

	}
}
