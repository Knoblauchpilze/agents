
# include "Influence.hh"

namespace mas {
  namespace environment {

    Influence::Influence():
      m_emitter(nullptr),
      m_receiver(nullptr)
    {}

    Influence::~Influence() {}

    bool
    Influence::valid() const noexcept {
      return (m_emitter != nullptr && m_receiver != nullptr);
    }

    const Agent&
    Influence::emitter() const noexcept {
      return *m_emitter;
    }

    const MovingObject&
    Influence::receiver() const noexcept {
      return *m_receiver;
    }

    void
    Influence::setEmitter(Agent* obj) {
      m_emitter = obj;
    }

    void
    Influence::setReceiver(MovingObject* obj) {
      m_receiver = obj;
    }

  }
}
