#ifndef VECTOR2D_HXX_INCLUDED
#define VECTOR2D_HXX_INCLUDED

#include <cmath>
#include "Vector2d.h"

namespace utils
{
    inline double& Vector2d::x()
    {
        return m_x;
    }

    inline const double& Vector2d::x() const
    {
        return m_x;
    }

    inline void Vector2d::setX(const double& x)
    {
        m_x = x;
    }

    inline double& Vector2d::y()
    {
        return m_y;
    }

    inline const double& Vector2d::y() const
    {
        return m_y;
    }

    inline void Vector2d::setY(const double& y)
    {
        m_y = y;
    }

    inline double Vector2d::length() const
    {
        return std::sqrt(lengthSquared());
    }

    inline double Vector2d::lengthSquared() const
    {
        return m_x * m_x + m_y * m_y;
    }
}

#endif // VECTOR2D_HXX_INCLUDED
