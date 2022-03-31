#ifndef    ENVIRONMENT_HH
# define   ENVIRONMENT_HH

# include <unordered_map>
# include <core_utils/Uuid.hh>
# include <core_utils/CoreObject.hh>
# include "Manager.hh"
# include "MovingObject.hh"
# include "Agent.hh"
# include "Animat.hh"
# include "PhysicEngine.hh"

namespace mas {
  namespace environment {

    /// @brief - A convenience define representing an entity.
    using Entity = utils::Uuid;

  }

  class Environment: public utils::CoreObject {
    public:

      /**
       * @brief - Create a new environment.
       */
      Environment();

      /**
       * @brief - Release the resources used by the environment.
       */
      ~Environment();

      /**
       * @brief - Simulate the environment with the data defined
       *          in the time manager.
       * @param manager - information about the time data of the
       *                  simulation.
       */
      void
      simulate(const time::Manager& manager);

    private:

      /**
       * @brief - Perform the needed operations to execute before the
       *          agents are executed.
       * @param manager - information about the time in the simulation.
       */
      void
      computePreAgentsStep(const time::Manager& manager);

      /**
       * @brief - Perform the needed operations to execute the agents
       *          in the simulation.
       * @param manager - information about the time in the simulation.
       */
      void
      computeAgentsStep(const time::Manager& manager);

      /**
       * @brief - Perform the needed operations to execute after the
       *          agents have been executed.
       * @param manager - information about the time in the simulation.
       */
      void
      computePostAgentsStep(const time::Manager& manager);

    private:

      /// @brief - The list of entities registered in the environment.
      using Entities = std::unordered_set<environment::Entity>;

      /// @brief - A list of the environmental objects registered in
      /// the environment. This includes every physical object.
      using Objects = std::vector<environment::MovingObjectShPtr>;

      /// @brief - A list of agents.
      using Agents = std::vector<environment::AgentShPtr>;

      /// @brief - A list of animats: these objects ake the binding
      /// between a brain (an agent) and its body (a moving object).
      using Animats = std::vector<environment::Animat>;

      /**
       * @brief - The list of entities registered in the world.
       */
      Entities m_entities;

      /**
       * @brief - The list of objects registered for this environment.
       */
      Objects m_objects;

      /**
       * @brief - The list of agents registered for this environment.
       */
      Agents m_agents;

      /**
       * @brief - The list of animats registered for this environment.
       */
      std::vector<environment::AnimatShPtr> m_animats;

      /**
       * @brief - The engine allowing to simulate physics in the
       *          environment. Each object is registered in it as
       *          soon as they are spawned and unregistered when
       *          they are deleted.
       */
      environment::PhysicEngine m_physic;
  };

}

#endif    /* ENVIRONMENT_HH */
