
# include "Influence.hh"

namespace mas {
  namespace environment {

    Influence::Influence():
      m_emitter(nullptr),
      m_receiver(nullptr)
    {}

    Influence::~Influence() {}

    bool
    Influence::valid() const {
      return (m_emitter != nullptr && m_receiver != nullptr);
    }

    const Object&
    Influence::emitter() const noexcept {
      return *m_emitter;
    }

    const Object&
    Influence::receiver() const noexcept {
      return *m_receiver;
    }

    void
    Influence::setEmitter(ObjectShPtr obj) {
      m_emitter = obj;
    }

    void
    Influence::setReceiver(ObjectShPtr obj) {
      m_receiver = obj;
    }

  }
}
