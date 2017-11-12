#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "Vector2d.h"

namespace utils
{
    namespace math
    {
        bool isOnLine(const utils::Vector2d& origin, const utils::Vector2d& direction, const utils::Vector2d& point);

        bool isOnSegment(const utils::Vector2d& p0, const utils::Vector2d& p1, const utils::Vector2d& point);

        utils::Vector2d intersectionPoint(const utils::Vector2d& origin1, const utils::Vector2d& direction1,
                                          const utils::Vector2d& origin2, const utils::Vector2d& direction2);
    }
}

#endif // MATHUTILS_H
