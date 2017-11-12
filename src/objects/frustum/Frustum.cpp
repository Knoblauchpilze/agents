
#include "Frustum.h"

namespace environment
{
    namespace objects
    {
        namespace frustum
        {
            Frustum::Frustum()
            {
                // Nothing to do.
            }

            Frustum::~Frustum()
            {
                // Nothing to do.
            }

            bool Frustum::intersects(const environment::objects::EnvironmentalObject& object) const
            {
                return object.getBoundingBox().intersects(asArea());
            }

            void Frustum::setPosition(const utils::Vector2d& position)
            {
                asArea().setX(position.x());
                asArea().setY(position.y());
            }
        }
    }
}
