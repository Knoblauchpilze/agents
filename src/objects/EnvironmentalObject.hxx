#ifndef ENVIRONMENTALOBJECT_HXX_INCLUDED
#define ENVIRONMENTALOBJECT_HXX_INCLUDED

#include "EnvironmentalObject.h"

namespace environment
{
    namespace objects
    {
        inline const environment::box::BoundingBox& EnvironmentalObject::getBoundingBox() const
        {
            return m_box;
        }

        inline environment::box::BoundingBox& EnvironmentalObject::getBoundingBox()
        {
            return m_box;
        }

        inline const environment::physics::RigidBodyShPtr EnvironmentalObject::getRigidBody() const
        {
            return m_rigidBody;
        }

        inline environment::physics::RigidBodyShPtr EnvironmentalObject::getRigidBody()
        {
            return m_rigidBody;
        }
    }
}

#endif // ENVIRONMENTALOBJECT_HXX_INCLUDED
