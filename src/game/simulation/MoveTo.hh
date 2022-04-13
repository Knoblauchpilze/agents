#ifndef    MOVE_TO_HH
# define   MOVE_TO_HH

# include "Behavior.hh"

namespace mas {
  namespace environment {

    class MoveTo: public Behavior {
      public:

        /**
         * @brief - Create a new behavior to move to somewhere.
         */
        MoveTo();

        /**
         * @brief - Implementation of the interface method to indicate
         *          whether this behavior is completed or not.
         * @return - `true` if the behavior is completed.
         */
        bool
        completed() const noexcept override;

        /**
         * @brief - Implementation of the interface method to perform
         *          the execution of the behavior. This will make the
         *          agent try to stick to the other agents visible and
         *          maintain a certain distance with all of them.
         * @param perceptions - the list of perceptions.
         * @param manager - information about the time at the moment
         *                  of the execution of the behavior.
         * @return - the list of influences defining the output of
         *           this behavior.
         */
        std::vector<InfluenceShPtr>
        perform(const AgentData& data,
                const Perceptions& perceptions,
                const time::Manager& manager) override;

      private:
    };

  }
}

#endif    /* MOVE_TO_HH */
