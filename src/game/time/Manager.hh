#ifndef    TIME_MANAGER_HH
# define   TIME_MANAGER_HH

# include <deque>
# include <core_utils/CoreObject.hh>

namespace mas {
 namespace time {

    /// @brief - Defines common units for a duration.
    enum class Unit {
      Nanosecond,
      Millisecond,
      Second,
      Minute,
      Hour,
      Day
    };

    /**
     * @brief - Convert a time unit to a human readable string.
     * @param unit - the unit to convert.
     * @return - the string representing the unit.
     */
    std::string
    unitToString(const Unit& unit) noexcept;

    class Manager: public utils::CoreObject {
      public:

        /**
         * @brief - Defines a new time manager with the specified time
         *          origin and the unit used to interpret it.
         * @param origin - the initial timestamp.
         * @param unit - the unit of the origin timestamp.
         * @param frames - define how many frames will be saved internally.
         */
        Manager(float origin = 0.0f,
                const Unit& unit = Unit::Second,
                unsigned frames = 10u);

        /**
         * @brief - Increment the duration elapsed since the origin by
         *          the corresponding time.
         * @param delta - the duration elapsed.
         * @param unit - the unit in which the `delta` is expressed.
         */
        void
        increment(float delta, const Unit& unit = Unit::Second) noexcept;

        /**
         * @brief - Decrement the duration elapsed since the origin by
         *          the corresponding time.
         * @param delta - the duration elapsed.
         * @param unit - the unit in which the `delta` is expressed.
         */
        void
        decrement(float deta, const Unit& unit = Unit::Second) noexcept;

        /**
         * @brief - Return the duration of the last step expressed in
         *          the specified unit.
         * @param unit - the unit in which the last step duration should
         *               be expressed.
         * @return - the duration of the last step.
         */
        float
        lastStepDuration(const Unit& unit = Unit::Second) const noexcept;

        /**
         * @brief - Return the duration elapsed since the origin of time
         *          in the specified unit.
         * @param unit - the desired conversion unit.
         * @return - the elapsed duration in the specified unit.
         */
        float
        elapsed(const Unit& unit = Unit::Second) const noexcept;

      private:

        /**
         * @brief - Perform the update of the internal timestamp considering
         *          that it is updated by the input value.
         * @param d - the duration to change the internal timestamp.
         * @param unit - the unit in which the duration is expressed.
         */
        void
        handleTimeModification(float d, const Unit& unit) noexcept;

      private:

        /// @brief - A definition of a frame: this defines a duration
        /// and a unit.
        using Frame = std::pair<float, Unit>;

        /**
         * @brief - The current time unit in which the time manager
         *          internally saves the elapsed time.
         */
        Unit m_unit;

        /**
         * @brief - The number of intervals of the defined time unit
         *          elapsed since the origin of time.
         */
        float m_time;

        /**
         * @brief - How many frames are allowed to be saved in the
         *          internal list of frames we save.
         */
        unsigned m_maxFrames;

        /**
         * @brief - The last frames.
         */
        std::deque<Frame> m_frames;
    };

  }
}

#endif    /* TIME_MANAGER_HH */
