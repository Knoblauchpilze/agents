
# include "Animat.hh"

namespace mas {
  namespace environment {

    Animat::Animat(MovingObjectShPtr obj):
      utils::CoreObject("animat"),

      m_agent(nullptr),
      m_body(obj),

      /// TODO: Update bbox for frustum.
      m_frustum(obj->bbox()),
      m_perceptions(),
      m_influences()
    {
      setService("mas");
    }

    AgentShPtr
    Animat::spawnAgent() {
      if (m_agent == nullptr) {
        m_agent = std::make_shared<Agent>(*this);
      }

      return m_agent;
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

  }
}
