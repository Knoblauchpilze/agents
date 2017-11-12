
#include <vector>
#include <algorithm>
#include "Area.h"
#include "MathUtils.h"

namespace utils
{
	namespace sdl
	{

		Area::Area(const double& x, const double& y, const double& width, const double& height) :
			m_x(x),
			m_y(y),
			m_w(width),
			m_h(height)
		{
			// Nothing to do
		}

        bool Area::contains(const utils::sdl::Area& other) const
        {
            if (other.getLeftBound() < getLeftBound())
            {
                return false;
            }
            if (other.getRightBound() > getRightBound())
            {
                return false;
            }
            if (other.getTopBound() > getTopBound())
            {
                return false;
            }
            if (other.getBottomBound() < getBottomBound())
            {
                return false;
            }
            return true;
        }

        bool Area::intersects(const utils::sdl::Area& other) const
        {
            if (other.getRightBound() < getLeftBound())
            {
                return false;
            }
            if (other.getLeftBound() > getRightBound())
            {
                return false;
            }
            if (other.getTopBound() < getBottomBound())
            {
                return false;
            }
            if (other.getBottomBound() > getTopBound())
            {
                return false;
            }
            return true;
        }

        bool Area::isInside(const utils::sdl::Area& other) const
        {
            if (other.getLeftBound() >= getLeftBound() &&
                other.getRightBound() <= getRightBound() &&
                other.getTopBound() <= getTopBound() &&
                other.getBottomBound() >= getBottomBound())
            {
                return true;
            }
            return false;
        }

        bool Area::isInside(const utils::Vector2d& point) const
        {
            if (getLeftBound() > point.x() || getRightBound() < point.x())
            {
                return false;
            }
            if (getBottomBound() > point.y() || getTopBound() < point.y())
            {
                return false;
            }
            return true;
        }

        utils::Vector2d Area::getNearestPoint(const utils::Vector2d& point) const
        {
            const double nearestX(getLeftBound() > point.x() ? getLeftBound() : (getRightBound() < point.x() ? getRightBound() : point.x()));
            const double nearestY(getBottomBound() > point.y() ? getBottomBound() : (getTopBound() < point.y() ? getTopBound() : point.y()));
            return utils::Vector2d(nearestX, nearestY);
        }

        utils::Vector2d Area::getNearestPointAlongDirection(const utils::Vector2d& point, const utils::Vector2d& direction) const
        {
            // If the point is not inside the box the input direction does not matter.
            if (!isInside(point))
            {
                return getNearestPoint(point);
            }
            // The point is inside the box. We need to compute the closest point along the direction which lies on the boundary of this area.
            // First, we need to determine of which border lies the closest point: to do so we can use the input direction.
            // Compute intersections with all 4 borders.
            const utils::Vector2d topRightCorner(m_x + m_w / 2.0, m_y + m_h / 2.0);
            const utils::Vector2d topLeftCorner(m_x - m_w / 2.0, m_y + m_h / 2.0);
            const utils::Vector2d bottomLeftCorner(m_x - m_w / 2.0, m_y - m_h / 2.0);
            const utils::Vector2d bottomRightCorner(m_x + m_w / 2.0, m_y - m_h / 2.0);

            const utils::Vector2d x(1.0, 0.0);
            const utils::Vector2d y(0.0, 1.0);

            const utils::Vector2d pointOnRightBorder(utils::math::intersectionPoint(point, direction, bottomRightCorner, y));
            const utils::Vector2d pointOnTopBorder(utils::math::intersectionPoint(point, direction, topLeftCorner, x));
            const utils::Vector2d pointOnLeftBorder(utils::math::intersectionPoint(point, direction, bottomLeftCorner, y));
            const utils::Vector2d pointOnBottomBorder(utils::math::intersectionPoint(point, direction, bottomLeftCorner, x));

            // Check which ones are actually on the borders.
            const bool isOnRightBorder(utils::math::isOnSegment(bottomRightCorner, topRightCorner, pointOnRightBorder));
            const bool isOnTopBorder(utils::math::isOnSegment(topLeftCorner, topRightCorner, pointOnTopBorder));
            const bool isOnLeftBorder(utils::math::isOnSegment(bottomLeftCorner, topLeftCorner, pointOnLeftBorder));
            const bool isOnBottomBorder(utils::math::isOnSegment(bottomLeftCorner, bottomRightCorner, pointOnBottomBorder));

            // Compute the dot product between the each point and the input direction.
            const double dotRight((pointOnRightBorder - point) * direction);
            const double dotTop((pointOnTopBorder - point) * direction);
            const double dotLeft((pointOnLeftBorder - point) * direction);
            const double dotBottom((pointOnBottomBorder - point) * direction);

            // Now select the point which has both lower dot product and is on the border.
            std::vector<std::pair<double, bool>> choice = {
                std::make_pair(dotRight, isOnRightBorder),
                std::make_pair(dotTop, isOnTopBorder),
                std::make_pair(dotLeft, isOnLeftBorder),
                std::make_pair(dotBottom, isOnBottomBorder)
            };
            std::sort(choice.begin(), choice.end(), [](const std::pair<double, bool>& d1, const std::pair<double, bool>& d2) {
                      return d1.first < d2.first;
            });
            for(auto it : choice)
            {
                std::cout << "[POINT] p=" << it.first << ", val=" << it.second << std::endl;
            }
            return utils::Vector2d();
        }

		//=====================

		SDL_Rect createTopLeftBasedRectFromArea(const Area& area) {
			SDL_Rect outputRect = { static_cast<short int>(area.getX()), static_cast<short int>(area.getY()), static_cast<short unsigned int>(area.getWidth()), static_cast<short unsigned int>(area.getHeight()) };
			return outputRect;
		}

		SDL_Rect createCenteredBasedRectFromArea(const Area& area) {
			SDL_Rect outputRect = { static_cast<short int>(area.getLeftBound()), static_cast<short int>(area.getTopBound()), static_cast<short unsigned int>(area.getWidth()), static_cast<short unsigned int>(area.getHeight()) };
			return outputRect;
		}

	}
}
