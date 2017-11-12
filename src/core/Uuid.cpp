
#include "Uuid.h"

namespace core
{
    namespace uuid
    {
        unsigned int Uuid::s_nextUuid(0u);

        Uuid::Uuid():
            m_uuid(s_nextUuid)
        {
            ++s_nextUuid;
        }

        Uuid::~Uuid()
        {
            // Nothing to do.
        }

        bool Uuid::operator==(const Uuid& other) const
        {
            return (m_uuid == other.m_uuid);
        }

        bool Uuid::operator!=(const Uuid& other) const
        {
            return !operator==(other);
        }
    }
}
