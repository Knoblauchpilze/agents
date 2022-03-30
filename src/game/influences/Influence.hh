#ifndef    INFLUENCE_HH
# define   INFLUENCE_HH

# include <memory>

namespace mas {
  namespace environment {

    /// @brief - Forward declaration of an environmental object.
    class Object;

    /// @brief - A shared pointer on an environmental object.
    using ObjectShPtr = std::shared_ptr<Object>;

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
        const Object&
        emitter() const noexcept;

        /**
         * @brief - Returns the receiver attached to the influence.
         *          In case the influence doesn't have any UB will
         *          occur.
         * @return - the receiver of the influence.
         */
        const Object&
        receiver() const noexcept;

        /**
         * @brief - Defines a new emitter for the influence. In case
         *          the object is null, nothing happens.
         * @param obj - the new emitter.
         */
        void
        setEmitter(ObjectShPtr obj);

        /**
         * @brief - Defines a new receiver for the influence. In case
         *          the object is null, nothing happens.
         * @param obj - the new receiver.
         */
        void
        setReceiver(ObjectShPtr obj);

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
        ObjectShPtr m_emitter;

        /**
         * @brief - The receiver of the influence.
         */
        ObjectShPtr m_receiver;
    };

    /// @brief - A shared pointer on an influence object.
    using InfluenceShPtr = std::shared_ptr<Influence>;
  }
}

#endif    /* INFLUENCE_HH */
