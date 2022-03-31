#ifndef    ANIMAT_HH
# define   ANIMAT_HH

# include <vector>
# include <memory>
# include <core_utils/CoreObject.hh>
# include "Influence.hh"
# include "MovingObject.hh"
# include "Perception.hh"
# include "Frustum.hh"
# include "Agent.hh"

namespace mas {
  namespace environment {

    class Animat: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new animat from the input moving object.
         * @param obj - the moving object attached to this animat.
         */
        Animat(MovingObjectShPtr obj);

        /**
         * @brief - Used to generate the agent that will be used by
         *          this animat to think. Calling this method more
         *          than one will return the same agent.
         * @return - the created agent.
         */
        AgentShPtr
        spawnAgent();

        /**
         * @brief - Return the frustum attached to this animat. This
         *          helps defining the perceptions that are visible
         *          to it.
         * @return - the frustum of the animat.
         */
        const Frustum&
        frustum() const noexcept;

        /**
         * @brief - Influence the object attached to the animat.
         * @param inf - the influence to register.
         */
        void
        influence(InfluenceShPtr inf);

        /**
         * @brief - Retrieve the perceptions attached to this animat.
         * @return - the perceptions attached to this object.
         */
        const Perceptions&
        perceptions() const noexcept;

        /**
         * @brief - Consume the influences currently registered in the
         *          animat. After calling this method the list of the
         *          influences will be empty.
         * @return - the list of influences for the animat.
         */
        std::vector<InfluenceShPtr>
        consumeInfluences() noexcept;

        /**
         * @brief - Set the perceptions for the animat given the current
         *          position of the body to the input list.
         * @param perceptions - the new perceptions available for this
         *                      animat. It will replace any existing
         *                      perceptions.
         */
        void
        perceive(Perceptions& perceptions);

      private:

        /**
         * @brief - The agent attached to this animat. This is the
         *          brain of the animat.
         */
        AgentShPtr m_agent;

        /**
         * @brief - The moving object attached to this animat. This
         *          is the body of the animat.
         */
        MovingObjectShPtr m_body;

        /**
         * @brief - The view frustum for this agent.
         */
        Frustum m_frustum;

        /**
         * @brief - The list of perceptions that were registered for
         *          this animat. They are supposed to be valid when
         *          the agent requests them but are not controlled by
         *          the animat.
         */
        Perceptions m_perceptions;

        /**
         * @brief - The influences that were submitted for this animat.
         *          Represent the next actions that will influence the
         *          body of this animat.
         */
        std::vector<InfluenceShPtr> m_influences;
    };

    using AnimatShPtr = std::shared_ptr<Animat>;
  }
}

#endif    /* ANIMAT_HH */
