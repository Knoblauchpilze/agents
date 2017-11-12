#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include "Vector2d.h"

namespace utils
{
	class Vector3d
	{
	    public:

            Vector3d(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0);

            ~Vector3d();

            Vector3d(const Vector3d& other);

            Vector3d& operator=(const Vector3d& other);

            inline double& x();

            inline const double& x() const;

            inline void setX(const double& x);

            inline double& y();

            inline const double& y() const;

            inline void setY(const double& y);

            inline double& z();

            inline const double& z() const;

            inline void setZ(const double& z);

            inline double length() const;

            inline double lengthSquared() const;

            double operator*(const Vector3d& other) const;

            bool operator==(const Vector3d& other) const;

            Vector3d operator+(const Vector3d& other) const;

            Vector3d& operator+=(const Vector3d& other);

            Vector3d operator-(const Vector3d& other) const;

            Vector3d operator-() const;

            Vector3d& operator-=(const Vector3d& other);

            Vector3d operator*(const double& scale) const;

            Vector2d toVector2d() const;

        private:

            double m_x;
            double m_y;
            double m_z;
	};

	Vector3d operator*(const double& scale, const Vector3d& vector);

	std::ostream& operator<<(const Vector3d& vec, std::ostream& out);

	std::ostream& operator<<(std::ostream& out, const Vector3d& vec);
}

#include "Vector3d.hxx"

#endif // VECTOR3D_H
