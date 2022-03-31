#ifndef    MOVING_OBJECT_HH
# define   MOVING_OBJECT_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Box.hh>
# include <maths_utils/Vector2.hh>
# include "RigidBody.hh"
# include "Manager.hh"

namespace mas {
  namespace environment {

    class MovingObject: public utils::CoreObject {
      public:

        /**
         * @brief - Create a new moving object from the input area.
         * @param area - the area of the moving object.
         * @param body - the rigid body attached to this object.
         */
        MovingObject(const utils::Boxf& area,
                     const RigidBody& body);

        /**
         * @brief - The bounding box attached to this object.
         * @return - the bounding box of the object.
         */
        const utils::Boxf&
        bbox() const noexcept;

        /**
         * @brief - Return the acceleration of this moving object.
         * @return - the acceleration of the object.
         */
        const utils::Vector2f&
        acceleration() const noexcept;

        /**
         * @brief - Return the speed of this moving object.
         * @return - the speed of the object.
         */
        const utils::Vector2f&
        speed() const noexcept;

        /**
         * @brief - Return whether or not the other moving object
         *          is in intersection with this one.
         * @param rhs - the moving object to check for intersection.
         * @return - `true` if the other object intersects this one.
         */
        bool
        intersects(const MovingObject& rhs) const noexcept;

        /**
         * @brief - Apply the input force to the object, to the
         *          limits defined by this object.
         * @param f - the force to apply.
         */
        void
        applyForce(const utils::Vector2f& f);

        /**
         * @brief - Simulate the dynamic processes attached to the
         *          moving object.
         * @param manager - the time manager.
         */
        void
        simulate(const time::Manager& manager);

      protected:

        /**
         * @brief - Clamp the input force to stay within the limits
         *          that this object can handle.
         * @param force - the force to clamp.
         */
        void
        clampForce(utils::Vector2f& force) const noexcept;

      private:

        /**
         * @brief - The rigid body attached to this object.
         */
        RigidBody m_body;

        /**
         * @brief - The area for this object.
         */
        utils::Boxf m_area;

        /**
         * @brief - The force currently applied to this object.
         */
        utils::Vector2f m_force;

        /**
         * @brief - The current acceleration of this object.
         */
        utils::Vector2f m_acceleration;

        /**
         * @brief - The current speed of this object.
         */
        utils::Vector2f m_speed;
    };

    using MovingObjectShPtr = std::shared_ptr<MovingObject>;
  }
}

#endif    /* MOVING_OBJECT_HH */
