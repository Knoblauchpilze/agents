#ifndef RECTANGLEFRUSTUM_H
#define RECTANGLEFRUSTUM_H

#include "Area.h"
#include "Frustum.h"

namespace environment
{
    namespace objects
    {
        namespace frustum
        {
            class RectangleFrustum: public Frustum
            {
                public:

                    RectangleFrustum(const utils::sdl::Area& area);

                    virtual ~RectangleFrustum();

                    virtual const utils::sdl::Area& asArea() const;

                protected:

                    virtual utils::sdl::Area& asArea();

                private:

                    utils::sdl::Area m_area;
            };

            using RectangleFrustumShPtr = std::shared_ptr<RectangleFrustum>;
        }
    }
}

#endif // RECTANGLEFRUSTUM_H
