#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

namespace utils
{
	class Vector2d
	{
	    public:

            explicit Vector2d(const double& x = 0.0, const double& y = 0.0);

            ~Vector2d();

            Vector2d(const Vector2d& other);

            Vector2d& operator=(const Vector2d& other);

            inline double& x();

            inline const double& x() const;

            inline void setX(const double& x);

            inline double& y();

            inline const double& y() const;

            inline void setY(const double& y);

            inline double length() const;

            inline double lengthSquared() const;

            double normalize();

            Vector2d& normalized();

            double operator*(const Vector2d& other) const;

            bool operator==(const Vector2d& other) const;

            bool operator!=(const Vector2d& other) const;

            Vector2d operator+(const Vector2d& other) const;

            Vector2d& operator+=(const Vector2d& other);

            Vector2d operator-(const Vector2d& other) const;

            Vector2d operator-() const;

            Vector2d& operator-=(const Vector2d& other);

            Vector2d operator*(const double& scale) const;

            Vector2d& operator*=(const double& scale);

            Vector2d operator/(const double& scale) const;

            Vector2d& operator/=(const double& scale);

        private:

            double m_x;
            double m_y;
    };

    Vector2d operator*(const double& scale, const Vector2d& vector);

    std::ostream& operator<<(const Vector2d& vec, std::ostream& out);

    std::ostream& operator<<(std::ostream& out, const Vector2d& vec);
}

#include "Vector2d.hxx"

#endif // VECTOR3D_H
