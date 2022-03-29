#ifndef INFLUENCE_H
#define INFLUENCE_H

#include "Agent.h"
#include "Body.h"
#include <memory>

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

			class Influence
			{
			    public:

			        Influence();

			        virtual ~Influence();

                    bool valid() const;

                    const environment::agents::Agent& getEmitter() const;

                    const environment::objects::Body& getReceiver() const;

                    void setEmitter(const std::shared_ptr<environment::agents::Agent> agent);

                    void setReceiver(const std::shared_ptr<environment::objects::Body> body);

                    virtual void apply() = 0;

                protected:

                    environment::agents::Agent& getEmitter();

                    environment::objects::Body& getReceiver();

                private:

                    std::shared_ptr<environment::agents::Agent> m_agent;
                    std::shared_ptr<environment::objects::Body> m_body;
			};

			using InfluenceShPtr = std::shared_ptr<Influence>;
		}
	}
}

#endif // INFLUENCE_H
