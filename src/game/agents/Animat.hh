#ifndef    ANIMAT_HH
# define   ANIMAT_HH

# include <vector>
# include <memory>
# include "Influence.hh"
# include "MovingObject.hh"
# include "Perception.hh"
# include "Frustum.hh"
# include "Agent.hh"
# include "Component.hh"
# include "AgentData.hh"

namespace mas {
  namespace environment {

    class Animat: public Component {
      public:

        /**
         * @brief - Create a new animat from the input moving object.
         * @param obj - the moving object attached to this animat.
         */
        Animat(MovingObject* obj);

        /**
         * @brief - Implementation of the interface method to handle
         *          the update of this component with the underlying
         *          data.
         */
        void
        update() override;

        /**
         * @brief - Used to plug the input agent and attached it to
         *          this animat as a brain. Calling this method more
         *          than one will override any existing agent.
         * @param agent - the agent to attach to the animat.
         */
        void
        plug(Agent* agent);

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

        /**
         * @brief - Retrieve the properties of the animat that can be
         *          used for the behaviors processing.
         * @return - the data related to the behavior.
         */
        AgentData
        data() const noexcept;

      private:

        /**
         * @brief - The agent attached to this animat. This is the
         *          brain of the animat.
         */
        Agent* m_agent;

        /**
         * @brief - The moving object attached to this animat. This
         *          is the body of the animat.
         */
        MovingObject* m_body;

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
