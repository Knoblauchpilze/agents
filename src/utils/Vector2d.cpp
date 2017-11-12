
#include <cmath>
#include "Vector2d.h"
#include "ComparisonUtils.h"

namespace utils
{
	Vector2d::Vector2d(const double& x, const double& y):
		m_x(x),
		m_y(y)
	{
		// Nothing to do
	}

	Vector2d::~Vector2d()
	{
		// Nothing to do
	}

	Vector2d::Vector2d(const Vector2d& other):
		m_x(other.m_x),
		m_y(other.m_y)
	{
		// Nothing to do
	}

	double Vector2d::normalize()
	{
	    const double thisLength(length());
	    if (!utils::comparison::doubleEqual(thisLength, 0.0))
        {
            m_x /= thisLength;
            m_y /= thisLength;
        }
        return thisLength;
	}

	Vector2d& Vector2d::normalized()
	{
	    normalize();
	    return (*this);
	}

	Vector2d& Vector2d::operator=(const Vector2d& other)
	{
		if (other == *this)
            {
			return *this;
		}
		m_x = other.m_x;
		m_y = other.m_y;
		return (*this);
	}

	double Vector2d::operator*(const Vector2d& other) const
	{
		return  m_x * other.m_x + m_y * other.m_y;
	}

	bool Vector2d::operator==(const Vector2d& other) const
	{
		return (utils::comparison::doubleEqual(m_x, other.m_x) &&
			utils::comparison::doubleEqual(m_y, other.m_y));
	}

	bool Vector2d::operator!=(const Vector2d& other) const
	{
		return !operator==(other);
	}

	Vector2d Vector2d::operator+(const Vector2d& other) const
	{
		Vector2d sum(*this);
		sum += other;
		return sum;
	}

	Vector2d& Vector2d::operator+=(const Vector2d& other)
	{
		m_x += other.m_x;
		m_y += other.m_y;
		return (*this);
	}

	Vector2d Vector2d::operator-(const Vector2d& other) const
	{
		Vector2d diff(*this);
		diff -= other;
		return diff;
	}

	Vector2d Vector2d::operator-() const
	{
	    Vector2d minus;
	    minus -= (*this);
	    return minus;
	}

	Vector2d& Vector2d::operator-=(const Vector2d& other)
	{
		m_x -= other.m_x;
		m_y -= other.m_y;
		return (*this);
	}

	Vector2d Vector2d::operator*(const double& scale) const
	{
		Vector2d multiply(*this);
		multiply.m_x *= scale;
		multiply.m_y *= scale;
		return multiply;
	}

	Vector2d& Vector2d::operator*=(const double& scale)
	{
	    m_x *= scale;
	    m_y *= scale;
	    return *this;
	}

	Vector2d Vector2d::operator/(const double& scale) const
	{
		Vector2d divide(*this);
		divide.m_x /= scale;
		divide.m_y /= scale;
		return divide;
	}

    Vector2d& Vector2d::operator/=(const double& scale)
    {
	    m_x /= scale;
	    m_y /= scale;
	    return *this;
    }

    double Vector2d::operator^(const Vector2d& other) const
    {
        return m_x * other.m_y - m_y * other.m_x;
    }

	// Non-member functions
	Vector2d operator*(const double& scale, const Vector2d& vector)
	{
		return vector * scale;
	}

	std::ostream& operator<<(const Vector2d& vec, std::ostream& out)
	{
	    out << vec.x() << "x" << vec.y();
        return out;
	}

	std::ostream& operator<<(std::ostream& out, const Vector2d& vec)
	{
	    return operator<<(vec, out);
	}
}
