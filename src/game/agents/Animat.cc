
# include "Animat.hh"

namespace mas {
  namespace environment {

    Animat::Animat(MovingObject* obj):
      Component(Type::Animat),

      m_agent(nullptr),
      m_body(obj),

      m_frustum(obj->bbox()),
      m_perceptions(),
      m_influences()
    {
      setService("mas");
    }

    void
    Animat::update() {
      m_frustum = Frustum(m_body->bbox());
    }

    void
    Animat::plug(Agent* agent) {
      m_agent = agent;
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
