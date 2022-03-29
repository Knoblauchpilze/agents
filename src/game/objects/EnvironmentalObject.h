#ifndef ENVIRONMENTALOBJECT_H
#define ENVIRONMENTALOBJECT_H

#include <memory>
#include <vector>
#include "RigidBody.h"
#include "BoundingBox.h"
#include "TimeManager.h"
#include "EnvironmentalObjectListener.h"

namespace environment
{
    namespace objects
    {
        class EnvironmentalObjectListener;

        class EnvironmentalObject
        {
            public:

                EnvironmentalObject(const double& x,
                                    const double& y,
                                    const double& width,
                                    const double& height,
                                    const double& density,
                                    const double& elasticity = 0.65);

                virtual ~EnvironmentalObject();

                inline const environment::box::BoundingBox& getBoundingBox() const;

                inline const environment::physics::RigidBodyShPtr getRigidBody() const;

                void addListener(environment::objects::EnvironmentalObjectListener* listener);

                virtual void applyEndogenous(const environment::time::TimeManager& manager);

            protected:

                void fireObjectModification();

                inline environment::box::BoundingBox& getBoundingBox();

                inline environment::physics::RigidBodyShPtr getRigidBody();

            private:

                environment::box::BoundingBox m_box;
                environment::physics::RigidBodyShPtr m_rigidBody;

                std::vector<EnvironmentalObjectListener*> m_listeners;
        };

        using EnvironmentalObjectShPtr = std::shared_ptr<EnvironmentalObject>;
    }
}

#include "EnvironmentalObject.hxx"

#endif // ENVIRONMENTALOBJECT_H
