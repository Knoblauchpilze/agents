
#include "BoundingBox.h"

namespace environment
{
    namespace box
    {
        BoundingBox::BoundingBox(const utils::sdl::Area& area):
            m_area(area)
        {
            // Nothing to do.
        }

        BoundingBox::BoundingBox(const double& x, const double& y, const double& width, const double& height):
            m_area(x, y, width, height)
        {
            // Nothing to do.
        }

        BoundingBox::~BoundingBox()
        {
            // Nothing to do.
        }

        bool BoundingBox::contains(const BoundingBox& other) const
        {
            return contains(other.m_area);
        }

        bool BoundingBox::intersects(const BoundingBox& other) const
        {
            return intersects(other.m_area);
        }

        bool BoundingBox::isInside(const BoundingBox& other) const
        {
            return isInside(other.m_area);
        }

        bool BoundingBox::contains(const utils::sdl::Area& other) const
        {
            return m_area.contains(other);
        }

        bool BoundingBox::intersects(const utils::sdl::Area& other) const
        {
            return m_area.intersects(other);
        }

        bool BoundingBox::isInside(const utils::sdl::Area& other) const
        {
            return m_area.isInside(other);
        }

        const utils::sdl::Area& BoundingBox::asArea() const
        {
            return m_area;
        }

        void BoundingBox::translate(const utils::Vector2d& translation)
        {
            m_area.setX(m_area.getX() + translation.x());
            m_area.setY(m_area.getY() + translation.y());
        }

        void BoundingBox::setPosition(const utils::Vector2d& translation)
        {
            m_area.setX(translation.x());
            m_area.setY(translation.y());
        }
    }
}
