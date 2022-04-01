#ifndef    ENTITY_HH
# define   ENTITY_HH

# include <vector>
# include <memory>
# include <core_utils/CoreObject.hh>
# include <core_utils/Uuid.hh>
# include "Component.hh"

namespace mas {
  namespace environment {

    class Entity: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new empty entity with no components.
         */
        Entity();

        /**
         * @brief - Return the type of this component.
         * @return - the type of the component.
         */
        const utils::Uuid&
        uuid() const noexcept;

        /**
         * @brief - The number of components attached to this entity.
         * @return - the number of components.
         */
        std::size_t
        components() const noexcept;

        /**
         * @brief - Add a new component to this entity. The component
         *          is checked so that it's not null.
         * @param comp - the component to add.
         */
        void
        add(ComponentShPtr comp);

        /**
         * @brief - Unregister the input component from the entity. If
         *          the component does not exist, nothing happens.
         * @param comp - the component to remove.
         */
        void
        erase(ComponentShPtr comp);

        /**
         * @brief - Erase any component registered in the entity based
         *          on their type.
         * @param kind - the kind of comopnent to erase from the entity.
         */
        void
        erase(const Type& kind);

        /// @brief - An iterator to handle the components of an entity
        /// in a simple and intuitive way.
        class iterator {
          public:

            /**
             * @brief - Comparison of iterators.
             * @param rhs - the iterator to compare to.
             * @return - `true` if this and rhs are equal.
             */
            bool
            operator==(const iterator& rhs) const noexcept;

            /**
             * @brief - Comparison of iterators.
             * @param rhs - the iterator to compare to.
             * @return - `true` if this and rhs are different.
             */
            bool
            operator!=(const iterator& rhs) const noexcept;

            /**
             * @brief - Return the current component pointed to by the
             *          iterator as a reference.
             * @return - the component pointed to by the iterator.
             */
            Component&
            operator*() const noexcept;

            /**
             * @brief - Return the current component pointed to by the
             *          iterator as a reference.
             * @return - the component pointed to by the iterator.
             */
            ComponentShPtr
            operator->() const noexcept;

            /**
             * @brief - Move the iterator to the next value.
             * @return - a reference to the iterator.
             */
            iterator&
            operator++() noexcept;

            /**
             * @brief - Post-fixed version of the increment operator
             *          which returns a new operator advanced by one
             *          but leaves the current one unchanged.
             * @return - a new operator moved one step forward.
             */
            iterator
            operator++(int) noexcept;

          private:

            /**
             * @brief - Creates a new iterator to iterate on the components
             *          of the specified entity.
             * @param ent - the entity linked to this iterator.
             * @param id - the index to start in the components array.
             */
            iterator(const Entity* ent, std::size_t id) noexcept;

          private:

            /// @brief - Allow the entity class to access to this one.
            friend class Entity;

            /**
             * @brief - The entity attached to this iterator.
             */
            const Entity* m_ent;

            /**
             * @brief - The current index of the component which
             *          was reached.
             */
            unsigned m_current;
        };

        /**
         * @brief - Return an iterator on the components attached to the
         *          entity with the specified type.
         * @param t - the type of components to iterate onto.
         * @return - an iterator for this entity.
         */
        iterator
        begin() const noexcept;

        /**
         * @brief - Return an iterator on the components attached to the
         *          entity with the specified type but past the end.
         * @param t - the type of components to iterate onto.
         * @return - an iterator for this entity.
         */
        iterator
        end() const noexcept;

      private:

        /// @brief - Convenience define for a list of components.
        using Components = std::vector<ComponentShPtr>;

        /// @brief - Allow the iterator class to access to this one.
        friend class const_iterator;

        /**
         * @brief - The uuid of the entity.
         */
        utils::Uuid m_uuid;

        /**
         * @brief - The list of components registered for this entity.
         */
        Components m_components;
    };

    using EntityShPtr = std::shared_ptr<Entity>;
  }
}

#endif    /* ENTITY_HH */
