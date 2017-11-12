
#include "EnvironmentalObject.h"

namespace environment
{
    namespace objects
    {
        EnvironmentalObject::EnvironmentalObject(const double& x,
                                                 const double& y,
                                                 const double& width,
                                                 const double& height,
                                                 const double& density,
                                                 const double& elasticity):
            m_box(x, y, width, height),
            m_rigidBody(std::make_shared<physics::RigidBody>(m_box.asArea(), density, elasticity)),
            m_listeners()
        {
            // Nothing to do.
        }

        EnvironmentalObject::~EnvironmentalObject()
        {
            // Nothing to do.
        }

        void EnvironmentalObject::addListener(environment::objects::EnvironmentalObjectListener* listener)
        {
            m_listeners.push_back(listener);
        }

        void EnvironmentalObject::applyEndogenous(const environment::time::TimeManager&)
        {
            // Do nothing.
        }

		void EnvironmentalObject::fireObjectModification()
		{
		    for (std::vector<EnvironmentalObjectListener*>::iterator listener = m_listeners.begin() ;
                listener != m_listeners.end() ;
                ++listener)
            {
                (*listener)->onObjectChanged(*this);
            }
		}
    }
}
