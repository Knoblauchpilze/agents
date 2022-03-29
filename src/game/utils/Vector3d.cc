
#include "Vector3d.h"
#include "ComparisonUtils.h"

namespace utils
{
	Vector3d::Vector3d(const double& x, const double& y, const double& z) :
		m_x(x),
		m_y(y),
		m_z(z)
	{
		// Nothing to do
	}

	Vector3d::~Vector3d() {
		// Nothing to do
	}

	Vector3d::Vector3d(const Vector3d& other) :
		m_x(other.m_x),
		m_y(other.m_y),
		m_z(other.m_z)
	{
		// Nothing to do
	}

	Vector3d& Vector3d::operator=(const Vector3d& other) {
		if (other == *this) {
			return *this;
		}
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
		return (*this);
	}

	double Vector3d::operator*(const Vector3d& other) const {
		return  m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
	}

	bool Vector3d::operator==(const Vector3d& other) const {
		return (utils::comparison::doubleEqual(m_x, other.m_x) &&
			utils::comparison::doubleEqual(m_y, other.m_y) &&
			utils::comparison::doubleEqual(m_z, other.m_z));
	}

	Vector3d Vector3d::operator+(const Vector3d& other) const {
		Vector3d sum(*this);
		sum += other;
		return sum;
	}

	Vector3d& Vector3d::operator+=(const Vector3d& other) {
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		return (*this);
	}

	Vector3d Vector3d::operator-(const Vector3d& other) const {
		Vector3d diff(*this);
		diff -= other;
		return diff;
	}

	Vector3d Vector3d::operator-() const
	{
	    Vector3d minus;
	    minus -= (*this);
	    return minus;
	}

	Vector3d& Vector3d::operator-=(const Vector3d& other) {
		m_x -= other.m_x;
		m_y -= other.m_y;
		m_z -= other.m_z;
		return (*this);
	}

	Vector3d Vector3d::operator*(const double& scale) const {
		Vector3d multiply(*this);
		multiply.m_x *= scale;
		multiply.m_y *= scale;
		multiply.m_z *= scale;
		return multiply;
	}

	Vector2d Vector3d::toVector2d() const
	{
	    return Vector2d(m_x, m_y);
	}

	// Non-member functions
	Vector3d operator*(const double& scale, const Vector3d& vector) {
		return vector * scale;
	}

	std::ostream& operator<<(const Vector3d& vec, std::ostream& out)
	{
	    out << vec.x() << "x" << vec.y() << "x" << vec.z();
        return out;
	}

	std::ostream& operator<<(std::ostream& out, const Vector3d& vec)
	{
	    return operator<<(vec, out);
	}
}
