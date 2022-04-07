#ifndef    INFLUENCE_HH
# define   INFLUENCE_HH

# include <memory>
# include "MovingObject.hh"
# include "Agent.hh"

namespace mas {
  namespace environment {

    /// @brief - A convenience define representing a callback for
    /// the application of an influence on the receiver.
    using ReceiverCallback = std::function<void(MovingObject&)>;

    /// @brief - A convenience define representing a callback for
    /// the application of an influence on the emitter.
    using EmitterCallback = std::function<void(Agent&)>;

    namespace influence {

      /**
       * @brief - A convenience define for a callback that has no
       *          effect on the emitter
       * @return - a no-op callback.
       */
      EmitterCallback
      noOpEmitter() noexcept;

      /**
       * @brief - A convenience define for a callback that has no
       *          effect on the receiver.
       * @retrun - a no-op callback.
       */
      ReceiverCallback
      noOpReceiver() noexcept;

    }

    class Influence {
      public:

        /**
         * @brief - Create a new empty influence. This will have
         *          no impact.
         * @param eCB - the callback defining the effect of this
         *              influence on the emitter.
         * @param rCB - the callback defining the effect of this
         *              influence on the receiver.
         */
        Influence(EmitterCallback eCB,
                  ReceiverCallback rCB);

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
        void
        apply() const;

      private:

        /**
         * @brief - The emitter of the influence.
         */
        Agent* m_emitter;

        /**
         * @brief - The receiver of the influence.
         */
        MovingObject* m_receiver;

        /**
         * @brief - The callback defining the effect of the influence
         *          on the emitter.
         */
        EmitterCallback m_eCallback;

        /**
         * @brief - The callback defining the effect of the influence
         *          on the receiver.
         */
        ReceiverCallback m_rCallback;
    };

    /// @brief - A shared pointer on an influence object.
    using InfluenceShPtr = std::shared_ptr<Influence>;
  }
}

#endif    /* INFLUENCE_HH */
