#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Area.h"
#include "Vector2d.h"

namespace environment
{
    namespace box
    {
        class BoundingBox
        {
            public:

                BoundingBox(const utils::sdl::Area& area);

                BoundingBox(const double& x, const double& y, const double& width, const double& height);

                ~BoundingBox();

                bool contains(const BoundingBox& other) const;

                bool intersects(const BoundingBox& other) const;

                bool isInside(const BoundingBox& other) const;

                bool contains(const utils::sdl::Area& other) const;

                bool intersects(const utils::sdl::Area& other) const;

                bool isInside(const utils::sdl::Area& other) const;

                const utils::sdl::Area& asArea() const;

                void translate(const utils::Vector2d& translation);

                void setPosition(const utils::Vector2d& translation);

            private:

                utils::sdl::Area m_area;

        };
    }
}

#endif // BOUNDINGBOX_H
