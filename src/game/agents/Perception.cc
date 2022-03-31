
# include "Perception.hh"

namespace mas {
  namespace environment {

    Perception::Perception(const MovingObject& object) :
      m_object(object)
    {}

    const utils::Boxf&
    Perception::bbox() const noexcept {
      return m_object.bbox();
    }

  }
}
