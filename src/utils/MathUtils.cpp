
#include "MathUtils.h"
#include "ComparisonUtils.h"

namespace utils
{
    namespace math
    {
        bool isOnLine(const utils::Vector2d& origin, const utils::Vector2d& direction, const utils::Vector2d& point)
        {
            return utils::comparison::doubleEqual((point - origin) ^ direction, 0.0);
        }

        bool isOnSegment(const utils::Vector2d& p0, const utils::Vector2d& p1, const utils::Vector2d& point)
        {
            if (!isOnLine(p0, p1 - p0, point))
            {
                // No need to continue further.
                return false;
            }
            const utils::Vector2d lineDirection(p1 - p0);
            // Choose the 'steepest' slope
            if (std::abs(lineDirection.x()) >= std::abs(lineDirection.y()))
            {
                return (lineDirection.x() > 0 ?
                        p0.x() <= point.x() && point.x() <= p1.x() :
                        p1.x() <= point.x() && point.x() <= p0.x());
            }
            else
            {
                return (lineDirection.y() > 0 ?
                        p0.y() <= point.y() && point.y() <= p1.y() :
                        p1.y() <= point.y() && point.y() <= p0.y());
            }
        }

        utils::Vector2d intersectionPoint(const utils::Vector2d& origin1, const utils::Vector2d& direction1,
                                          const utils::Vector2d& origin2, const utils::Vector2d& direction2)
        {
            // Check whether these lines are parallel.
            if (utils::comparison::doubleEqual(direction1 ^ direction2, 0.0))
            {
                // Check if both points are on the same line (i.e. origin2 - origin1 is parallel to the lines' direction)
                if (utils::comparison::doubleEqual((origin2 - origin1) ^ direction1, 0.0))
                {
                    return origin1;
                }
                // Lines do not intersect, return the first origin.
                return origin1;
            }
            // Compute using some... hum... formulas.
            const double denom(direction1.x() * direction2.y() - direction1.y() * direction2.x());
            const double firstNum(direction2.y() * (origin2.x() - origin1.x()));
            const double secondNum(direction2.x() * (origin2.y() - origin1.y()));
            const double t((firstNum - secondNum) / denom);
            return origin1 + t * direction1;
        }
    }
}
