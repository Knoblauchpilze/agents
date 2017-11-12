#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <memory>
#include <vector>
#include "Vector2d.h"
#include "Perception.h"
#include "Influence.h"

namespace environment
{
    namespace agents
    {
        namespace behaviors
        {
            class Behavior
            {
                public:

                    Behavior();

                    virtual ~Behavior();

                    virtual bool isComplete() const = 0;

                    virtual
                    std::vector<std::shared_ptr<environment::agents::influences::Influence>>
                    perform(const std::vector<environment::perceptions::Perception>& perceptions) = 0;

                protected:

                    using VectorOfPerceptions = std::vector<environment::perceptions::Perception>;

                    utils::Vector2d getNearestPoint(const utils::Vector2d& current, const environment::perceptions::Perception& perception) const;

            };

            using BehaviorShPtr = std::shared_ptr<Behavior>;
        }
    }
}

#endif // BEHAVIOR_H
