
# include "Animat.hh"

namespace mas {
  namespace environment {

    Animat::Animat(MovingObject* obj,
                   float speedMotionThreshold,
                   float frustumToBodyRatio):
      Component(Type::Animat),

      m_agent(nullptr),
      m_body(obj),

      m_speedMotionThreshold(speedMotionThreshold),
      m_frustumToBodyRatio(std::max(1.0f, frustumToBodyRatio)),
      m_frustum(obj->bbox().scale(m_frustumToBodyRatio)),
      m_perceptions(),
      m_influences()
    {
      setService("mas");
    }

    void
    Animat::simulate(const time::Manager& /*manager*/) {
      m_frustum = Frustum(m_body->bbox().scale(m_frustumToBodyRatio));
    }

    void
    Animat::plug(Agent* agent) {
      m_agent = agent;
    }

    bool
    Animat::isBody(MovingObject* obj) const noexcept {
      // We want a null object to never be considered as
      // a valid animat's body.
      return obj != nullptr && m_body == obj;
    }

    const Frustum&
    Animat::frustum() const noexcept {
      return m_frustum;
    }

    void
    Animat::influence(InfluenceShPtr inf) {
      // Consistency check.
      if (m_agent == nullptr || m_body == nullptr) {
        return;
      }

      // Force properties of this influence to match the
      // animat's internal properties.
      inf->setEmitter(m_agent);
      inf->setReceiver(m_body);

      m_influences.push_back(inf);
    }

    const Perceptions&
    Animat::perceptions() const noexcept {
      return m_perceptions;
    }

    std::vector<InfluenceShPtr>
    Animat::consumeInfluences() noexcept {
      std::vector<InfluenceShPtr> out;
      out.swap(m_influences);

      return out;
    }

    void
    Animat::perceive(Perceptions& perceptions) {
      m_perceptions.swap(perceptions);
    }

    AgentData
    Animat::data() const noexcept {
      return AgentData{
        m_body->bbox(),         // area
        m_body->speed(),        // speed
        m_speedMotionThreshold, // speed motion threshold
        m_body->acceleration()  // accel
      };
    }

  }
}
