#ifndef    AGENT_HH
# define   AGENT_HH

# include <memory>
# include <core_utils/RNG.hh>
# include "Component.hh"
# include "Manager.hh"

namespace mas {
  namespace environment {

    /// @brief - Forward declaration of the animat class.
    class Animat;

    /// @brief - Forward declaration of the behavior class.
    class Behavior;

    /// @brief - A pointer to a behavior.
    using BehaviorShPtr = std::shared_ptr<Behavior>;

    class Agent: public Component {
      public:

        /**
         * @brief - Create a new agent with the specified animat.
         */
        Agent(Animat& animat);

        /**
         * @brief - Implementation of the interface method to handle
         *          the update of this component with the underlying
         *          data.
         */
        void
        update() override;

        /**
         * @brief - Evaluate the decisions to take for this agent.
         *          This uses the data propagated in the body of
         *          the agent (which is its representation in the
         *          world) and output influences.
         * @param manager - information about the time at the moment
         *                  of the execution of this method.
         * @param rng - a device to produce random number generator.
         */
        void
        live(const time::Manager& manager,
             utils::RNG& rng);

      private:

        /**
         * @brief - Used to create a new behavior which will be then
         *          followed by the agent.
         * @param rng - a source of randomness.
         */
        void
        think(utils::RNG& rng);

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
