#ifndef    ENVIRONMENT_HH
# define   ENVIRONMENT_HH

# include <unordered_map>
# include <core_utils/Uuid.hh>
# include <core_utils/CoreObject.hh>
# include <core_utils/RNG.hh>
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
       * @brief - Return the random number generator associated
       *          to this environment.
       * @return - the randomness source for this environment.
       */
      utils::RNG&
      rng() noexcept;

      /**
       * @brief - Simulate the environment with the data defined
       *          in the time manager.
       * @param manager - information about the time data of the
       *                  simulation.
       */
      void
      simulate(const time::Manager& manager);

      /**
       * @brief - The number of agents currently registered in the
       *          simulation. We consider every entity having at
       *          least an agent component.
       * @return - the number of agents.
       */
      unsigned
      agents() const noexcept;

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

      /// @brief - The list of entities registered in the environment.
      using Entities = std::unordered_map<utils::Uuid, environment::EntityShPtr>;

    public:

      /// @brief - An iterator to handle the entities of an environment
      /// in a simple and intuitive way.
      class const_iterator {
        public:

          /**
           * @brief - Comparison of iterators.
           * @param rhs - the iterator to compare to.
           * @return - `true` if this and rhs are equal.
           */
          bool
          operator==(const const_iterator& rhs) const noexcept;

          /**
           * @brief - Comparison of iterators.
           * @param rhs - the iterator to compare to.
           * @return - `true` if this and rhs are different.
           */
          bool
          operator!=(const const_iterator& rhs) const noexcept;

          /**
           * @brief - Return the current entity pointed to by the
           *          iterator as a reference.
           * @return - the entity pointed to by the iterator.
           */
          const environment::Entity&
          operator*() const noexcept;

          /**
           * @brief - Return the current entity pointed to by the
           *          iterator as a reference.
           * @return - the entity pointed to by the iterator.
           */
          environment::EntityShPtr
          operator->() const noexcept;

          /**
           * @brief - Move the iterator to the next value.
           * @return - a reference to the iterator.
           */
          const_iterator&
          operator++() noexcept;

          /**
           * @brief - Post-fixed version of the increment operator
           *          which returns a new operator advanced by one
           *          but leaves the current one unchanged.
           * @return - a new operator moved one step forward.
           */
          const_iterator
          operator++(int) noexcept;

        private:

          /**
           * @brief - Creates a new iterator to iterate on the entities
           *          of the specified environment.
           * @param it - the iterator to start with in the entities map.
           */
          const_iterator(Entities::const_iterator it) noexcept;

        private:

          /// @brief - Allow the environment class to access to this one.
          friend class Environment;

          /**
           * @brief - The current index of the entity we reached.
           */
          Entities::const_iterator m_current;
      };

      /**
       * @brief - Return an iterator on the entities registered in
       *          the environment
       * @return - an iterator for this environment.
       */
      const_iterator
      cbegin() const noexcept;

      /**
       * @brief - Return an iterator on the entities registered in
       *          the environment but past the end.
       * @return - an iterator for this environment.
       */
      const_iterator
      cend() const noexcept;

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

      /// @brief - Allow the iterator class to access to this one.
      friend class const_iterator;

      /**
       * @brief - The random number generator associated to this
       *          environment. Propagated to other components so
       *          that we have a single source of randomness.
       */
      utils::RNG m_rng;

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
