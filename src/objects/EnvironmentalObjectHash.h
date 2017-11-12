#ifndef ENVIRONMENTALOBJECTHASH_H_INCLUDED
#define ENVIRONMENTALOBJECTHASH_H_INCLUDED

namespace environment
{
    namespace objects
    {
        class EnvironmentalObject;
    }
}

namespace std
{
  template<>
  class hash<environment::objects::EnvironmentalObject>
  {
      public:

          inline size_t operator()(const environment::objects::EnvironmentalObject& object) const;
  };
}

#endif // ENVIRONMENTALOBJECTHASH_H_INCLUDED
