#ifndef    BEHAVIOR_HH
# define   BEHAVIOR_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Point2.hh>
# include "Influence.hh"
# include "Perception.hh"

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
         * @param perceptions - the list of perceptions.
         * @return - the list of influences defining the output of
         *           this behavior.
         */
        virtual
        std::vector<InfluenceShPtr>
        perform(const Perceptions& perceptions) = 0;

      protected:

        /**
         * @brief - Return the nearest point from the input position
         *          to the perception but still belonging to the
         *          perception.
         * @param p - the point from which the nearest point should
         *            be computed.
         * @param perception - the perception to compute.
         * @return - a point representing the nearest position.
         */
        utils::Point2f
        nearest(const utils::Point2f& p, const Perception& perception) const noexcept;
    };

    using BehaviorShPtr = std::shared_ptr<Behavior>;
  }
}

#endif    /* BEHAVIOR_HH */
