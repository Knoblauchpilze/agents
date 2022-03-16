
#include "RectangleFrustum.h"

namespace environment
{
    namespace objects
    {
        namespace frustum
        {
            RectangleFrustum::RectangleFrustum(const utils::sdl::Area& area):
                Frustum(),
                m_area(area)
            {
                // Nothing to do.
            }

            RectangleFrustum::~RectangleFrustum()
            {
                // Nothing to do.
            }

            const utils::sdl::Area& RectangleFrustum::asArea() const
            {
                return m_area;
            }

            //==========

            utils::sdl::Area& RectangleFrustum::asArea()
            {
                return m_area;
            }
        }
    }
}
