
# include "Impulse.hh"

/// @brief - The threshold below which the speed is considered
/// null and would trigger a new impulse.
# define SPEED_THRESHOLD 0.1f

namespace mas {
  namespace environment {

    ImpulseBehavior::ImpulseBehavior(const utils::Vector2f& impulse, bool repeat):
      Behavior(),

      m_impulse(impulse),
      m_repeat(repeat),

      m_impulsed(false)
    {}

    bool
    ImpulseBehavior::completed() const noexcept {
      return m_impulsed && !m_repeat;
    }

    std::vector<InfluenceShPtr>
    ImpulseBehavior::perform(const AgentData& data,
                             const Perceptions& /*perceptions*/,
                             const time::Manager& /*manager*/)
    {
      // Check whether we should give an impulse.
      bool slow = data.speed.length() < SPEED_THRESHOLD;

      std::vector<InfluenceShPtr> out;

      if (!m_impulsed || slow) {
        // Create the influence representing the impulse.
        utils::Vector2f i = m_impulse;
        InfluenceShPtr inf = std::make_shared<Influence>(
          [i](MovingObject& obj) {
            obj.applyForce(i);
          }
        );
        out.push_back(inf);

        log(
          "Impulsing agent at " + data.area.toString() + " by " + m_impulse.toString() +
          " speed: " + data.speed.toString() + " (length: " + std::to_string(data.speed.length()) + ")"
        );

        // We created an impulse.
        m_impulsed = true;
      }

      return out;
    }

  }
}
