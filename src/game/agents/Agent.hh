#ifndef    AGENT_HH
# define   AGENT_HH

# include <memory>
# include <core_utils/CoreObject.hh>

namespace mas {
  namespace environment {

    /// @brief - Forward declaration of the animat class.
    class Animat;

    /// @brief - Forward declaration of the behavior class.
    class Behavior;

    /// @brief - A pointer to a behavior.
    using BehaviorShPtr = std::shared_ptr<Behavior>;

    class Agent: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new agent with the specified animat.
         */
        Agent(Animat& animat);

        /**
         * @brief - Evaluate the decisions to take for this agent.
         *          This uses the data propagated in the body of
         *          the agent (which is its representation in the
         *          world) and output influences.
         */
        void
        live();

      private:

        /**
         * @brief - Used to create a new behavior which will be then
         *          followed by the agent.
         */
        void
        think();

      private:

        /**
         * @brief - The animat attached to this agent.
         */
        Animat& m_animat;

        /**
         * @brief - The current behavior followed by this agent.
         */
        BehaviorShPtr m_behavior;
    };

    using AgentShPtr = std::shared_ptr<Agent>;
  }
}

#endif    /* AGENT_HH */
