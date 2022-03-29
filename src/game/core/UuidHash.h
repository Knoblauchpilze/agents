#ifndef UUIDHASH_H_INCLUDED
#define UUIDHASH_H_INCLUDED

#include <functional>

namespace core
{
    namespace uuid
    {
        class Uuid;
    }
}

namespace std
{
    template<>
    class hash<core::uuid::Uuid>
    {
        public:

            inline size_t operator()(const core::uuid::Uuid& object) const;
  };
}

#endif // UUIDHASH_H_INCLUDED
