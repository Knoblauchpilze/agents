
# include "Perception.hh"

namespace mas {
  namespace environment {

    Perception::Perception(const MovingObject& object, const UserData* data) :
      m_object(object),
      m_data(data)
    {}

    const utils::Boxf&
    Perception::bbox() const noexcept {
      return m_object.bbox();
    }

    bool
    Perception::hasUserData() const noexcept {
      return m_data != nullptr;
    }

  }
}
