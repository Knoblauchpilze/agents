#ifndef PERCEPTION_H
#define PERCEPTION_H

#include <memory>
#include "EnvironmentalObject.h"

namespace environment
{
	namespace perceptions
    {
        class Perception
        {
            public:

                Perception(const objects::EnvironmentalObject& object);

                virtual ~Perception();

                const environment::box::BoundingBox& getBoundingBox() const;

            private:

                const objects::EnvironmentalObject* m_object;
        };

        using PerceptionShPtr = std::shared_ptr<Perception>;
    }
}

#endif // PERCEPTION_H
