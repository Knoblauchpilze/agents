#ifndef    COMPONENT_HXX
# define   COMPONENT_HXX

# include "Component.hh"

namespace mas {
  namespace environment {

    template <typename T>
    inline
    const T*
    Component::as() const noexcept {
      return dynamic_cast<const T*>(this);
    }

    template <typename T>
    inline
    T*
    Component::as() noexcept {
      return dynamic_cast<T*>(this);
    }

  }
}

#endif    /* COMPONENT_HXX */
