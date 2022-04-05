
# include "Component.hh"
# include "Entity.hh"

namespace mas {
  namespace environment {

    std::string
    typeToString(const Type& t) noexcept {
      switch (t) {
        case Type::MovingObject:
          return "moving";
        case Type::Agent:
          return "agent";
        case Type::Animat:
          return "animat";
        case Type::Renderer:
          return "renderer";
        default:
          return "unknown";
      }
    }

    Component::Component(const Type& type):
      utils::CoreObject(typeToString(type)),

      m_type(type)
    {
      setService("mas");
    }

    const Type&
    Component::type() const noexcept {
      return m_type;
    }

    void
    Component::attach(const Entity& ent) noexcept {
      // Define a new name for the component so that it matches
      // the name of the entity.
      setName(ent.uuid().toString());
    }

  }
}
