#ifndef    IMPULSE_HH
# define   IMPULSE_HH

# include "Behavior.hh"

namespace mas {
  namespace environment {

    class ImpulseBehavior: public Behavior {
      public:

        /**
         * @brief - Create a new impulse behavior with the specified
         *          impulse.
         * @param impulse - the impulse to generate.
         * @param repeat - whether or not the impulse will repeat.
         */
        ImpulseBehavior(const utils::Vector2f& impulse, bool repeat);

        /**
         * @brief - Implementation of the interface method to indicate
         *          whether this behavior is completed or not.
         * @return - `true` if the behavior is completed.
         */
        bool
        completed() const noexcept override;

        /**
         * @brief - Implementation of the interface method to perform
         *          the execution of the behavior. This will communicate
         *          an impulse to the agent as an influence when the
         *          speed is not sufficient enough.
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

        /**
         * @brief - The impulse to apply to the receiver of this
         *          behavior.
         */
        utils::Vector2f m_impulse;

        /**
         * @brief - Whether or not the impulse should be repeated.
         */
        bool m_repeat;

        /**
         * @brief - Whether or not the impulse was given at least
         *          once.
         */
        bool m_impulsed;
    };

  }
}

#endif    /* IMPULSE_HH */
