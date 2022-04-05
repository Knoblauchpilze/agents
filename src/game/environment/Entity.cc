
# include "Entity.hh"
# include <algorithm>

namespace mas {
  namespace environment {

    Entity::Entity():
      utils::CoreObject("entity"),

      m_uuid(utils::Uuid::create()),

      m_components()
    {
      // Update the name of the entity to be its identifier.
      setName(m_uuid.toString());
      setService("mas");
    }

    const utils::Uuid&
    Entity::uuid() const noexcept {
      return m_uuid;
    }

    std::size_t
    Entity::components() const noexcept {
      return m_components.size();
    }

    void
    Entity::add(ComponentShPtr comp) {
      if (comp == nullptr) {
        warn(
          "Failed to register component for entity",
          "Invalid null component"
        );

        return;
      }

      comp->attach(*this);

      log("Registering " + typeToString(comp->type()) + " component to entity");
      m_components.push_back(comp);
    }

    void
    Entity::erase(ComponentShPtr comp) {
      std::size_t s = components();

      Components::iterator newEnd = std::remove_if(
        m_components.begin(), m_components.end(),
        [&comp](ComponentShPtr c) {
          return c.get() == comp.get();
        }
      );

      m_components.erase(newEnd);

      if (components() != s) {
        log("Removed component with kind " + typeToString(comp->type()));
      }
    }

    void
    Entity::erase(const Type& kind) {
      std::size_t s = components();

      Components::iterator newEnd = std::remove_if(
        m_components.begin(), m_components.end(),
        [&kind](ComponentShPtr c) {
          return c->type() == kind;
        }
      );

      m_components.erase(newEnd);

      if (components() != s) {
        log("Removed " + std::to_string(s - components()) + " component(s) with kind " + typeToString(kind));
      }
    }

    ComponentShPtr
    Entity::get(const Type& t) const noexcept {
      unsigned id = 0u;

      while (id < m_components.size()) {
        if (m_components[id]->type() == t) {
          return m_components[id];
        }
        ++id;
      }

      return nullptr;
    }

    bool
    Entity::hasComponent(const Type& t) const noexcept {
      return get(t) != nullptr;
    }

    void
    Entity::update() {
      for (unsigned id = 0u ; id < m_components.size() ; ++id) {
        m_components[id]->update();
      }
    }

    Entity::iterator
    Entity::begin() const noexcept {
      return iterator(this, 0u);
    }

    Entity::iterator
    Entity::end() const noexcept {
      return iterator(this, components());
    }

    Entity::iterator::iterator(const Entity* ent, std::size_t id) noexcept:
      m_ent(ent),
      m_current(id)
    {}

    bool
    Entity::iterator::operator==(const iterator& rhs) const noexcept {
      return m_ent == rhs.m_ent && m_current == rhs.m_current;
    }

    bool
    Entity::iterator::operator!=(const iterator& rhs) const noexcept {
      return !operator==(rhs);
    }

    Component&
    Entity::iterator::operator*() const noexcept {
      return *m_ent->m_components[m_current];
    }

    ComponentShPtr
    Entity::iterator::operator->() const noexcept {
      return m_ent->m_components[m_current];
    }

    Entity::iterator&
    Entity::iterator::operator++() noexcept {
      ++m_current;
      return *this;
    }

    Entity::iterator
    Entity::iterator::operator++(int) noexcept {
      return iterator(m_ent, m_current++);
    }

  }
}
