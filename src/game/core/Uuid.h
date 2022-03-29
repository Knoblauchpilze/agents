#ifndef UUID_H
#define UUID_H

#include "UuidHash.h"

namespace core
{
    namespace uuid
    {
        class Uuid
        {
            public:

                Uuid();

                ~Uuid();

                bool operator==(const Uuid& other) const;

                bool operator!=(const Uuid& other) const;

            private:

                friend size_t std::hash<Uuid>::operator()(const Uuid&) const;

                static unsigned int s_nextUuid;

                unsigned int m_uuid;
        };
    }
}

#include "Uuid.hxx"

#endif // UUID_H
