
# include "Influence.hh"

namespace mas {
  namespace environment {

    Influence::Influence(InflucenceCallback cb):
      m_emitter(nullptr),
      m_receiver(nullptr),

      m_callback(cb)
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
      m_callback(*m_receiver);
    }

  }
}
