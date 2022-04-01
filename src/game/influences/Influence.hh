#ifndef    INFLUENCE_HH
# define   INFLUENCE_HH

# include <memory>
# include "MovingObject.hh"
# include "Agent.hh"

namespace mas {
  namespace environment {

    class Influence {
      public:

        /**
         * @brief - Create a new empty influence. This will have
         *          no impact.
         */
        Influence();

        /**
         * @brief - Destruction of the object to allow virtual
         *          tables.
         */
        virtual ~Influence();

        /**
         * @brief - Whether the influence is valid (i.e. there's
         *          a valid emitter and a receiver).
         * @return - if the influence is valid.
         */
        bool
        valid() const noexcept;

        /**
         * @brief - Returns the emitter attached to the influence.
         *          In case the influence doesn't have any UB will
         *          occur.
         * @return - the emitter of the influence.
         */
        const Agent&
        emitter() const noexcept;

        /**
         * @brief - Returns the receiver attached to the influence.
         *          In case the influence doesn't have any UB will
         *          occur.
         * @return - the receiver of the influence.
         */
        const MovingObject&
        receiver() const noexcept;

        /**
         * @brief - Defines a new emitter for the influence. In case
         *          the object is null, nothing happens.
         * @param obj - the new emitter.
         */
        void
        setEmitter(Agent* obj);

        /**
         * @brief - Defines a new receiver for the influence. In case
         *          the object is null, nothing happens.
         * @param obj - the new receiver.
         */
        void
        setReceiver(MovingObject* obj);

        /**
         * @brief - Interface method to apply the influence to both the
         *          emitter and receiver.
         */
        virtual void
        apply() const = 0;

      private:

        /**
         * @brief - The emitter of the influence.
         */
        Agent* m_emitter;

        /**
         * @brief - The receiver of the influence.
         */
        MovingObject* m_receiver;
    };

    /// @brief - A shared pointer on an influence object.
    using InfluenceShPtr = std::shared_ptr<Influence>;
  }
}

#endif    /* INFLUENCE_HH */
