#ifndef ENVIRONMENTLISTENER_H
#define ENVIRONMENTLISTENER_H

namespace environment
{
    namespace listener
    {
        class EnvironmentListener
        {
            public:

                EnvironmentListener();

                virtual ~EnvironmentListener();

                virtual void onEnvironmentUpdate() = 0;

            protected:

            private:
        };
    }
}

#endif // ENVIRONMENTLISTENER_H
