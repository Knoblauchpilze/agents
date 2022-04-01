#ifndef    COMPONENT_HH
# define   COMPONENT_HH

# include <memory>
# include <core_utils/CoreObject.hh>

namespace mas {
  namespace environment {

    /// @brief - The various type of components.
    enum class Type {
      MovingObject,
      Agent,
      Animat,
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

      protected:

        /**
         * @brief - Create a new empty component with the required
         *          type.
         * @param type - the type of the component.
         */
        Component(const Type& type);

      private:

        /**
         * @brief - The type of the component.
         */
        Type m_type;
    };

    using ComponentShPtr = std::shared_ptr<Component>;
  }
}

# include "Component.hxx"

#endif    /* COMPONENT_HH */
