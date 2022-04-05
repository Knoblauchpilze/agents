
# include "Manager.hh"

namespace {

  float
  fromUnitToSecond(const mas::time::Unit& source) noexcept {
    switch (source) {
      case mas::time::Unit::Millisecond:
        return 0.001f;
      case mas::time::Unit::Minute:
          return 60.0f;
      case mas::time::Unit::Hour:
        return 60.0f * 60.0f;
      case mas::time::Unit::Day:
        return 60.0f * 60.0f * 24.0f;
      default:
        // Assume it is second
      case mas::time::Unit::Second:
        return 1.0f;
    }
  }

  float
  convertDuration(float d,
                  const mas::time::Unit& source,
                  const mas::time::Unit& target) noexcept
  {
    // Convert the source into seconds.
    float sec = d * fromUnitToSecond(source);

    // Convert back into desired unit.
    return sec / fromUnitToSecond(target);
  }

}

namespace mas {
  namespace time {

    std::string
    unitToString(const Unit& unit) noexcept {
      switch (unit) {
        case Unit::Nanosecond:
          return "nanosecond";
        case Unit::Millisecond:
          return "millisecond";
        case Unit::Second:
          return "second";
        case Unit::Minute:
          return "minute";
        case Unit::Hour:
          return "hour";
        case Unit::Day:
          return "day";
        default:
          return "unknown";
      }
    }

    Manager::Manager(float origin, const Unit& unit, unsigned frames):
      utils::CoreObject("time"),

      m_unit(unit),
      m_time(origin),

      m_maxFrames(frames),
      m_frames()
    {
      setService("mas");
    }

    void
    Manager::increment(float delta, const Unit& unit) noexcept {
      handleTimeModification(delta, unit);
    }

    void
    Manager::decrement(float delta, const Unit& unit) noexcept {
      handleTimeModification(-delta, unit);
    }

    float
    Manager::lastStepDuration(const Unit& unit) const noexcept {
      float last = 0.0f;

      if (!m_frames.empty()) {
        Frame lastFrame = m_frames.back();
        last = convertDuration(lastFrame.first, lastFrame.second, unit);
      }

      return last;
    }

    float
    Manager::elapsed(const Unit& unit) const noexcept {
      return convertDuration(m_time, m_unit, unit);
    }

    void
    Manager::handleTimeModification(float d, const Unit& unit) noexcept {
      double sec = convertDuration(d, unit, m_unit);

      m_time += sec;

      // Add the step to the buffer
      m_frames.push_back(std::make_pair(d, unit));
      if (m_frames.size() > m_maxFrames) {
        m_frames.pop_front();
      }
    }

  }
}
