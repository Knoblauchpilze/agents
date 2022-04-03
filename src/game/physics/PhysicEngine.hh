#ifndef    PHYSIC_ENGINE_HH
# define   PHYSIC_ENGINE_HH

# include <vector>
# include <unordered_set>
# include <core_utils/CoreObject.hh>
# include "MovingObject.hh"
# include "Manager.hh"
# include "CollisionSolver.hh"

namespace mas {
  namespace environment {

    class PhysicEngine: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new physic engine.
         */
        PhysicEngine();

        /**
         * @brief - Register a new moving object handled by this engine.
         *          Nothing happens in case the object is null.
         * @param obj - the object to register.
         */
        void
        registerObject(MovingObject* obj);

        /**
         * @brief - Unregister the input objecr from the list of bodies
         *          managed by this engine. Nothing happens in case
         *          the object is null or it not registered.
         * @param obj - the object to unregister.
         */
        void
        unregisterObject(MovingObject* obj);

        /**
         * @brief - Simulate the objects managed by the engine by handling
         *          the collisions and generally moving the objects.
         * @param manager - the time manager.
         */
        void
        simulate(const time::Manager& manager);

      private:

        /// @brief - The key generated for an object.
        using Key = intptr_t;

        /// @brief - A list of keys.
        using Keys = std::unordered_set<Key>;

        /**
         * @brief - The list of moving objects managed by this engine.
         */
        Objects m_objects;

        /**
         * @brief - The list of keys generated for objects.
         */
        Keys m_keys;
    };

  }
}

#endif  /* PHYSIC_ENGINE_HH */
