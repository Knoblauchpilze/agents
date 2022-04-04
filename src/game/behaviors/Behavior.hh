#ifndef    BEHAVIOR_HH
# define   BEHAVIOR_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Point2.hh>
# include "Influence.hh"
# include "Perception.hh"
# include "AgentData.hh"

namespace mas {
  namespace environment {

    class Behavior: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new behavior.
         */
        Behavior();

        virtual ~Behavior();

        /**
         * @brief - Whether or not this behavior is complete, meaning
         *          that it reached its completion.
         * @return - `true` if the behavior is completed.
         */
        virtual bool
        completed() const noexcept = 0;

        /**
         * @brief - Perform the behavior working with the input list
         *          of perceptions. We expect any inheriting class
         *          to return a list of influences (which defines the
         *          set of actions to perform for the behavior).
         * @param data - the data describing the agent.
         * @param perceptions - the list of perceptions.
         * @param manager - information about the time at the moment
         *                  of the execution of the behavior.
         * @return - the list of influences defining the output of
         *           this behavior.
         */
        virtual
        std::vector<InfluenceShPtr>
        perform(const AgentData& data,
                const Perceptions& perceptions,
                const time::Manager& manager) = 0;
    };

    using BehaviorShPtr = std::shared_ptr<Behavior>;
  }
}

#endif    /* BEHAVIOR_HH */
