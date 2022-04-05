#ifndef    AGENT_HH
# define   AGENT_HH

# include <memory>
# include <core_utils/RNG.hh>
# include "Component.hh"
# include "Manager.hh"
# include "AgentData.hh"
# include "Perception.hh"

namespace mas {
  namespace environment {

    /// @brief - Forward declaration of the animat class.
    class Animat;

    /// @brief - Forward declaration of the behavior class.
    class Behavior;

    /// @brief - A pointer to a behavior.
    using BehaviorShPtr = std::shared_ptr<Behavior>;

    namespace brain {

      /// @brief - A definition for the function to be applied
      /// to determine whether the agent needs to take a new
      /// decision.
      using BehaviorUpdate = std::function<bool(const AgentData&)>;

      /// @brief - Define a function used to create a new behavior
      /// for the agent when the previous one is not applicable
      /// or it was determined that a new behavior was needed.
      using BehaviorSelection = std::function<BehaviorShPtr(const AgentData&, const Perceptions&, utils::RNG&)>;

      /// @brief - Define a function to be called when the agent
      /// finished its current behavior.
      using BehaviorTermination = std::function<BehaviorShPtr(BehaviorShPtr)>;

    }

    class Agent: public Component {
      public:

        /**
         * @brief - Create a new agent with the specified animat.
         * @param animat - a reference to the animat attached to the
         *                 agent. It is the way the agent has to be
         *                 in touch with the world and influence it.
         * @param bUpdate - the callback to define when the behavior
         *                  of the agent should be updated.
         * @param bSelection - the callback to pick a new behavior.
         * @param bTermination - the callback to handle the behavior
         *                       once it is completed.
         */
        Agent(Animat& animat,
              brain::BehaviorUpdate bUpdate,
              brain::BehaviorSelection bSelection,
              brain::BehaviorTermination bTermination);

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
         * @brief - The animat attached to this agent.
         */
        Animat& m_animat;

        /**
         * @brief - The current behavior followed by this agent.
         */
        BehaviorShPtr m_behavior;

        /**
         * @brief - The callback to determine whether or not the
         *          agent needs a new behavior.
         */
        brain::BehaviorUpdate m_bUpdate;

        /**
         * @brief - The callback to create a new behavior in case
         *          it was determined that it is needed.
         */
        brain::BehaviorSelection m_bSelection;

        /**
         * @brief - The callback used to handle the behavior when
         *          it is completed.
         */
        brain::BehaviorTermination m_bTermination;
    };

    using AgentShPtr = std::shared_ptr<Agent>;
  }
}

#endif    /* AGENT_HH */
