#ifndef    ENVIRONMENT_HH
# define   ENVIRONMENT_HH

# include <vector>
# include <core_utils/Uuid.hh>
# include <core_utils/CoreObject.hh>
# include "Entity.hh"
# include "Manager.hh"
# include "PhysicEngine.hh"

namespace mas {

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
      using Entities = std::vector<environment::EntityShPtr>;

      /**
       * @brief - The list of entities registered in the world.
       */
      Entities m_entities;

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
