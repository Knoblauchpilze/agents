#ifndef    PERCEPTION_HXX
# define   PERCEPTION_HXX

# include "Perception.hh"

namespace mas {
  namespace environment {

    template <typename T>
    inline
    const T*
    Perception::as() const noexcept {
      return dynamic_cast<const T*>(m_data);
    }

  }
}

#endif    /* PERCEPTION_HXX */
