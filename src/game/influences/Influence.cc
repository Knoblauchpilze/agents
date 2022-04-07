
# include "Influence.hh"

namespace mas {
  namespace environment {
    namespace influence {

      EmitterCallback
      noOpEmitter() noexcept {
        return [](Agent& /*agent*/) {};
      }

      ReceiverCallback
      noOpReceiver() noexcept {
        return [](MovingObject& /*obj*/) {};
      }
    }

    Influence::Influence(EmitterCallback eCB,
                         ReceiverCallback rCB):
      m_emitter(nullptr),
      m_receiver(nullptr),

      m_eCallback(eCB),
      m_rCallback(rCB)
    {}

    Influence::~Influence() {}

    bool
    Influence::valid() const noexcept {
      return (m_emitter != nullptr && m_receiver != nullptr);
    }

    void
    Influence::setEmitter(Agent* obj) {
      m_emitter = obj;
    }

    void
    Influence::setReceiver(MovingObject* obj) {
      m_receiver = obj;
    }

    void
    Influence::apply() const {
      m_rCallback(*m_receiver);
      m_eCallback(*m_emitter);
    }

  }
}
