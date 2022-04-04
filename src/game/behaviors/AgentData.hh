#ifndef    AGENT_DATA_HH
# define   AGENT_DATA_HH

# include <maths_utils/Point2.hh>
# include <maths_utils/Box.hh>

namespace mas {
  namespace environment {

    /// @brief - Convenience define representing the data to pass
    /// to the behavior so that it can perform its processing.
    struct AgentData {
      // The area of the agent.
      const utils::Boxf& area;

      // The current speed of the agent.
      const utils::Vector2f& speed;

      // The current acceleration of the agent.
      const utils::Vector2f& accel;

      /**
       * @brief - Determine whether this agent is moving in any
       *          direction.
       * @return - `true` if the agent is moving.
       */
      bool
      moving() const noexcept;
    };

  }
}

#endif    /* AGENT_DATA_HH */
