#ifndef VECTOR3D_HXX_INCLUDED
#define VECTOR3D_HXX_INCLUDED

#include <cmath>
#include "Vector3d.h"

namespace utils
{
    inline double& Vector3d::x()
    {
        return m_x;
    }

    inline const double& Vector3d::x() const
    {
        return m_x;
    }

    inline void Vector3d::setX(const double& x)
    {
        m_x = x;
    }

    inline double& Vector3d::y()
    {
        return m_y;
    }

    inline const double& Vector3d::y() const
    {
        return m_y;
    }

    inline void Vector3d::setY(const double& y)
    {
        m_y = y;
    }

    inline double& Vector3d::z()
    {
        return m_z;
    }

    inline const double& Vector3d::z() const
    {
        return m_z;
    }

    inline void Vector3d::setZ(const double& z)
    {
        m_z = z;
    }

    inline double Vector3d::length() const
    {
        return std::sqrt(lengthSquared());
    }

    inline double Vector3d::lengthSquared() const
    {
        return m_x * m_x + m_y * m_y + m_z * m_z;
    }
}

#endif // VECTOR3D_HXX_INCLUDED
