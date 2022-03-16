
#include "Influence.h"

namespace environment
{
	namespace agents
	{
		namespace influences
		{
			Influence::Influence():
				m_agent(nullptr),
				m_body(nullptr)
			{
				// Nothing to do.
			}

			Influence::~Influence()
			{
				// Nothing to do.
			}

			bool Influence::valid() const
			{
				return (m_agent != nullptr && m_body != nullptr);
			}

			const Agent& Influence::getEmitter() const
			{
				return *m_agent;
			}

			const objects::Body& Influence::getReceiver() const
			{
				return *m_body;
			}

			void Influence::setEmitter(const environment::agents::AgentShPtr agent) {
				m_agent = agent;
			}

			void Influence::setReceiver(const environment::objects::BodyShPtr body) {
				m_body = body;
			}

			//================

			environment::agents::Agent& Influence::getEmitter() {
				return *m_agent;
			}

			environment::objects::Body& Influence::getReceiver() {
				return *m_body;
			}
		}
	}
}
