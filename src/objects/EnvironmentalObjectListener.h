#ifndef ENVIRONMENTALOBJECTLISTENER_H
#define ENVIRONMENTALOBJECTLISTENER_H

#include "EnvironmentalObject.h"

namespace environment
{
    namespace objects
    {
        class EnvironmentalObject;

        class EnvironmentalObjectListener
        {
            public:

                EnvironmentalObjectListener();

                virtual ~EnvironmentalObjectListener();

                virtual void onObjectChanged(const EnvironmentalObject& object) = 0;

            protected:

            private:
        };
    }
}

#endif // ENVIRONMENTALOBJECTLISTENER_H
