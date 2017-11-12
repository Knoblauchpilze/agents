#ifndef AREA_HXX_INCLUDED
#define AREA_HXX_INCLUDED

#include "Area.h"

namespace utils
{
    namespace sdl
    {
		double& Area::getX() {
			return m_x;
		}

		const double& Area::getX() const {
			return m_x;
		}

		double& Area::getY() {
			return m_y;
		}

		const double& Area::getY() const {
			return m_y;
		}

		double Area::getLeftBound() const {
			return m_x - m_w / 2.0;
		}

		double Area::getRightBound() const {
			return m_x + m_w / 2.0;
		}

		double Area::getTopBound() const {
			return m_y + m_h / 2.0;
		}

		double Area::getBottomBound() const {
			return m_y - m_h / 2.0;
		}

		double& Area::getWidth() {
			return m_w;
		}

		const double& Area::getWidth() const {
			return m_w;
		}

		double& Area::getHeight() {
			return m_h;
		}

		const double& Area::getHeight() const {
			return m_h;
		}

		void Area::setX(const double& x) {
			m_x = x;
		}

		void Area::setY(const double& y) {
			m_y = y;
		}

		void Area::setWidth(const double& width) {
			m_w = width;
		}

		void Area::setHeight(const double& height) {
			m_h = height;
		}

		double Area::getSurface() const {
			return m_w * m_h;
		}
    }
}

#endif // AREA_HXX_INCLUDED
