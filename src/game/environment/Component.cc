
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
        case Type::UserData:
          return "user-data";
        default:
          return "unknown";
      }
    }

    Component::Component(const Type& type):
      utils::CoreObject(typeToString(type)),

      m_type(type),
      m_uuid(),
      m_toBeDeleted(false)
    {
      setService("mas");
    }

    const Type&
    Component::type() const noexcept {
      return m_type;
    }

    const utils::Uuid&
    Component::uuid() const noexcept {
      return m_uuid;
    }

    bool
    Component::markedForDeletion() const noexcept {
      return m_toBeDeleted;
    }

    void
    Component::attach(const Entity& ent) noexcept {
      // Define a new module for the component so that it matches
      // the identifier of the entity.
      addModule(ent.uuid().toString());

      // Assign the same identifier as the entity.
      m_uuid = ent.uuid();
    }

    void
    Component::markForDeletion(bool mark) noexcept {
      m_toBeDeleted = mark;
    }

  }
}
