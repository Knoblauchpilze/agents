
#include "Behavior.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            Behavior::Behavior()
            {
                // Nothing to do.
            }

            Behavior::~Behavior()
            {
                // Nothing to do.
            }

            //====================

            utils::Vector2d Behavior::getNearestPoint(const utils::Vector2d& current, const environment::perceptions::Perception& perception) const
            {
                const utils::sdl::Area& box(perception.getBoundingBox().asArea());
                utils::Vector2d nearestPoint;

                if (current.x() <= box.getLeftBound())
                {
                    nearestPoint.x() = box.getLeftBound();
                }
                else if (current.x() >= box.getRightBound())
                {
                    nearestPoint.x() = box.getRightBound();
                }
                else
                {
                    nearestPoint.x() = current.x();
                }

                if (current.y() <= box.getBottomBound())
                {
                    nearestPoint.y() = box.getBottomBound();
                }
                else if (current.y() >= box.getTopBound())
                {
                    nearestPoint.y() = box.getTopBound();
                }
                else
                {
                    nearestPoint.y() = current.y();
                }

                return nearestPoint;
            }
        }
    }
}
