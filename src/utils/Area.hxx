#ifndef AREA_HXX_INCLUDED
#define AREA_HXX_INCLUDED

#include "Area.h"

namespace utils
{
    namespace sdl
    {
		inline double& Area::getX()
		{
			return m_x;
		}

		inline const double& Area::getX() const
		{
			return m_x;
		}

		inline double& Area::getY()
		{
			return m_y;
		}

		inline const double& Area::getY() const
		{
			return m_y;
		}

		inline double Area::getLeftBound() const
		{
			return m_x - m_w / 2.0;
		}

		inline double Area::getRightBound() const
		{
			return m_x + m_w / 2.0;
		}

		inline double Area::getTopBound() const
		{
			return m_y + m_h / 2.0;
		}

		inline double Area::getBottomBound() const
		{
			return m_y - m_h / 2.0;
		}

		inline utils::Vector2d Area::getCenter() const
		{
		    return utils::Vector2d(m_x, m_y);
		}

		inline utils::Vector2d Area::getTopLeftCorner() const
		{
		    return utils::Vector2d(m_x - m_w / 2.0, m_y + m_h / 2.0);
		}

        inline utils::Vector2d Area::getTopRightCorner() const
        {
            return utils::Vector2d(m_x + m_w / 2.0, m_y + m_h / 2.0);
        }

        inline utils::Vector2d Area::getBottomRightCorner() const
        {
            return utils::Vector2d(m_x + m_w / 2.0, m_y - m_h / 2.0);
        }

        inline utils::Vector2d Area::getBottomLeftCorner() const
        {
            return utils::Vector2d(m_x - m_w / 2.0, m_y - m_h / 2.0);
        }

		inline double& Area::getWidth()
		{
			return m_w;
		}

		inline const double& Area::getWidth() const
		{
			return m_w;
		}

		inline double& Area::getHeight()
		{
			return m_h;
		}

		inline const double& Area::getHeight() const
		{
			return m_h;
		}

		inline void Area::setX(const double& x)
		{
			m_x = x;
		}

		inline void Area::setY(const double& y)
		{
			m_y = y;
		}

		inline void Area::setWidth(const double& width)
		{
			m_w = width;
		}

		inline void Area::setHeight(const double& height)
		{
			m_h = height;
		}

		inline double Area::getSurface() const
		{
			return m_w * m_h;
		}
    }
}

#endif // AREA_HXX_INCLUDED
