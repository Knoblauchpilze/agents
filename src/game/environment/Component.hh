#ifndef    COMPONENT_HH
# define   COMPONENT_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include <core_utils/Uuid.hh>
# include "Manager.hh"

namespace mas {
  namespace environment {

    /// @brief - Forward declaration of the entity class.
    class Entity;

    /// @brief - The various type of components.
    enum class Type {
      MovingObject,
      Agent,
      Animat,
      Renderer,
      UserData,
    };

    /**
     * @brief - Convert the component type to a human readable string.
     * @param t - the component type to convert.
     * @return - a string representing this component.
     */
    std::string
    typeToString(const Type& t) noexcept;

    class Component: public utils::CoreObject {
      public:

        /**
         * @brief - Return the type of this component.
         * @return - the type of the component.
         */
        const Type&
        type() const noexcept;

        /**
         * @brief - Return the type of this component.
         * @return - the type of the component.
         */
        const utils::Uuid&
        uuid() const noexcept;

        /**
         * @brief - Whether this component needs to be deleted.
         * @return - `true` if the component needs to be deleted.
         */
        bool
        markedForDeletion() const noexcept;

        /**
         * @brief - Convert the component as the requested pointer type.
         *          In case the component is not the correct type, then
         *          the return value will be null.
         * @return - the component as a pointer to the dedicated type.
         */
        template <typename T>
        const T*
        as() const noexcept;

        /**
         * @brief - Convert the component as the requested pointer type.
         *          In case the component is not the correct type, then
         *          the return value will be null.
         * @return - the component as a pointer to the dedicated type.
         */
        template <typename T>
        T*
        as() noexcept;

        /**
         * @brief - Perform the update of the component so that it is up
         *          to date with the underlying data that it might be
         *          using.
         *          This method should be implemented by inheriting classes
         *          so that a specific behavior is provided.
         * @param manager - the time information at the moment of the
         *                  update.
         */
        virtual void
        simulate(const time::Manager& manager) = 0;

        /**
         * @brief - Used to configure the component as attached to a
         *          certain entity.
         * @param ent - the entity to which this component is attached.
         */
        void
        attach(const Entity& ent) noexcept;

      protected:

        /**
         * @brief - Create a new empty component with the required
         *          type.
         * @param type - the type of the component.
         */
        Component(const Type& type);

        /**
         * @brief - Update the deletion status to the input value.
         * @param mark - whether or not the component should be marked
         *               for deletion (default is `true`).
         */
        void
        markForDeletion(bool mark = true) noexcept;

      private:

        /**
         * @brief - The type of the component.
         */
        Type m_type;

        /**
         * @brief - The identifier of the component.
         */
        utils::Uuid m_uuid;

        /**
         * @brief - Whether or not the component should be deleted.
         */
        bool m_toBeDeleted;
    };

    using ComponentShPtr = std::shared_ptr<Component>;
  }
}

# include "Component.hxx"

#endif    /* COMPONENT_HH */
