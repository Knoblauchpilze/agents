
#include "Perception.h"

namespace environment
{
	namespace perceptions
    {
        Perception::Perception(const objects::EnvironmentalObject& object) :
            m_object(&object)
        {
            // Nothing to do
        }

        Perception::~Perception()
        {
            // Nothing to do, do NOT destroy the associated object
        }

        const environment::box::BoundingBox& Perception::getBoundingBox() const
        {
            return m_object->getBoundingBox();
        }
	}
}
