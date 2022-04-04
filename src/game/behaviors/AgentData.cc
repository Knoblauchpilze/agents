
# include "AgentData.hh"

/// @brief - The threshold indicating whether the agent is
/// still moving or not.
# define MOTION_SPEED_THRESHOLD 0.1f

namespace mas {
  namespace environment {

    bool
    AgentData::moving() const noexcept {
      return speed.length() >= MOTION_SPEED_THRESHOLD;
    }

  }
}
