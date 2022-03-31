#ifndef    RIGID_BODY_HH
# define   RIGID_BODY_HH

# include <memory>
# include <maths_utils/Box.hh>

namespace mas {
  namespace environment {

    class RigidBody {
      public:

        /**
         * @brief - Create a new rigid body with the specified area,
         *          mass and elasiticity.
         *          The user can set a negative mass, which will
         *          create an infinitely massive rigid body.
         * @param mass - the mass of the rigid body.
         * @param elasticity - the elasticity of the rigid body.
         * @param area - the area of the body.
         */
        RigidBody(float mass,
                  float elasticity,
                  const utils::Boxf& area) noexcept;

        /**
         * @brief - Whether this rigid body is infinitely massive.
         * @return - `true` if the body is infinitely massive.
         */
        bool
        infinitelyMassive() const noexcept;

        /**
         * @brief - The mass of the rigid body.
         * @return - the mass of the rigid body.
         */
        float
        mass() const noexcept;

        /**
         * @brief - The elasticity of the rigid body.
         * @return - the elasticity of the rigid body.
         */
        float
        elasticity() const noexcept;

      private:

        /**
         * @brief - The area of the rigid body.
         */
        utils::Boxf m_area;

        /**
         * @brief - The mass of the rigid body.
         */
        float m_mass;

        /**
         * @brief - The elasticity of the rigid body.
         */
        float m_elasticity;
    };

  }
}

#endif    /* RIGID_BODY_HH */
