#ifndef UUID_HXX_INCLUDED
#define UUID_HXX_INCLUDED

#include "Uuid.h"

/// Hash specialization.
namespace std {
    size_t hash<core::uuid::Uuid>::operator()(const core::uuid::Uuid& object) const
    {
        return std::hash<unsigned int>()(object.m_uuid);
    }
}

#endif // UUID_HXX_INCLUDED
