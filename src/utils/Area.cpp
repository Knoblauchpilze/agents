
#include "Area.h"

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
