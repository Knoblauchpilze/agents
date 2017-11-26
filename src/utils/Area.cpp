
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

            // Compute the dot product between each point and the input direction.
            const double dotRight((pointOnRightBorder - point) * direction);
            const double dotTop((pointOnTopBorder - point) * direction);
            const double dotLeft((pointOnLeftBorder - point) * direction);
            const double dotBottom((pointOnBottomBorder - point) * direction);

            /*std::cout << "....." << std::endl;
            std::cout << "[NEAREST] right=" << pointOnRightBorder << ", dot=" << dotRight << std::endl;
            std::cout << "[NEAREST] top=" << pointOnTopBorder << ", dot=" << dotTop << std::endl;
            std::cout << "[NEAREST] left=" << pointOnLeftBorder << ", dot=" << dotLeft << std::endl;
            std::cout << "[NEAREST] bottom=" << pointOnBottomBorder << ", dot=" << dotBottom << std::endl;*/

            // Build a vector where we put both points and the dot product with the initial direction.
            using Choice = std::pair<double, std::pair<std::string, utils::Vector2d>>;
            std::vector<Choice> choices = {
                std::make_pair(dotRight, std::make_pair("right", pointOnRightBorder)),
                std::make_pair(dotTop, std::make_pair("top", pointOnTopBorder)),
                std::make_pair(dotLeft, std::make_pair("left", pointOnLeftBorder)),
                std::make_pair(dotBottom, std::make_pair("bottom", pointOnBottomBorder))
            };
            // Sort by decreasing dot product.
            std::sort(choices.begin(), choices.end(), [](const Choice& d1, const Choice& d2) {
                return d1.first < d2.first;
            });
            // Now we need to select the final value: we need to find the negative dot product which is closest to 0.
            // Indeed we want the dot product to be negative, which means that the border is behind the current point (according to
            // the input direction) and close to 0 because we want the nearest point.
            // Keep only negative values.
            std::vector<Choice>::iterator finalValidChoice =
            std::remove_if(choices.begin(), choices.end(), [](const Choice& d) {
                return d.first >= 0.0;
            });
            // Erase the rest of the values.
            choices.erase(finalValidChoice, choices.end());

            /*for (auto t : choices)
            {
                std::cout << "[NEAR] p=" << t.first << ", " << t.second.first << ", " << t.second.second << std::endl;
            }
            std::cout << "[NEAREST] Keeping point " << choices.back().second.second << "dot=" << choices.back().first << " (name=" << choices.back().second.first << ")" << std::endl;
            std::cout << "....." << std::endl;*/

            // The last element of the choices vector should be the negative value closest to 0.
            return choices.back().second.second;
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
