#ifndef    OBJECTS_HH
# define   OBJECTS_HH

# include <maths_utils/Point2.hh>
# include "Environment.hh"
# include "UserData.hh"

namespace mas {
  namespace environment {

    /// @brief - Description of a user data component which lives
    /// for a certain duration and then request to be deleted.
    class Attractor: public UserData {
      public:

        /**
         * @brief - Build a new attractor with the input lifespan.
         * @param lifespan - the lifespan of the attractor in seconds.
         * @param attractiveness - the attractveness of this object.
         */
        Attractor(float lifespan, float attractiveness) noexcept;

        float
        attractiveness() const noexcept;

        void
        simulate(const time::Manager& manager) override;

      private:

        /**
         * @brief - The lifespan of the attractor.
         */
        float m_lifespan;

        /**
         * @brief - The attractiveness of the attractor.
         */
        float m_attractiveness;
    };

    /**
     * @brief - Generate a new attractor at the specified position
     *          and register it in the environment.
     * @param env - the environment in which the attractor should
     *              be spawned.
     * @param p - the position where the object should be spawned.
     * @param attractiveness - the attractiveness of the attractor.
     *                         Note that if the value is negative
     *                         this attractor will repel things.
     */
    void
    spawnAttractor(Environment& env,
                   const utils::Point2f& p,
                   float attractiveness) noexcept;

  }
}

#endif    /* OBJECTS_HH */
