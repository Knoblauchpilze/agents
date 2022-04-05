
# include "AgentData.hh"


namespace mas {
  namespace environment {

    bool
    AgentData::moving() const noexcept {
      return speed.length() >= speedMotionThreshold;
    }

  }
}
