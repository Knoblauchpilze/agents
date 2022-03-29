#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <memory>
#include "Vector2d.h"
#include "Area.h"
#include "EnvironmentalObject.h"

namespace environment
{
    namespace objects
    {
        namespace frustum
        {
            class Frustum
            {
                public:

                    Frustum();

                    virtual ~Frustum();

                    virtual const utils::sdl::Area& asArea() const = 0;

                    bool intersects(const environment::objects::EnvironmentalObject& object) const;

                    void setPosition(const utils::Vector2d& position);

                protected:

                    virtual utils::sdl::Area& asArea() = 0;

                private:
            };

            using FrustumShPtr = std::shared_ptr<Frustum>;
        }
    }
}

#endif // FRUSTUM_H
