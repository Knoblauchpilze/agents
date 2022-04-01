#ifndef    ENVIRONMENT_HH
# define   ENVIRONMENT_HH

# include <unordered_map>
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

      /**
       * @brief - Create a new entity and returns its identifier.
       *          No component is attached just yet.
       * @return - the identifier of the entity.
       */
      utils::Uuid
      createEntity() noexcept;

      /**
       * @brief - Register a new component to the entity specified
       *          by the identifier.
       * @param ent - the identifier of the entity to which the
       *              component will be added.
       * @param comp - the component to add to the entity.
       */
      void
      registerComponent(const utils::Uuid& ent, environment::ComponentShPtr comp);

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
      using Entities = std::unordered_map<utils::Uuid, environment::EntityShPtr>;

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
