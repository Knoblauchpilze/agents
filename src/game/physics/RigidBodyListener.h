#ifndef RIGIDBODYLISTENER_H
#define RIGIDBODYLISTENER_H

namespace environment
{
    namespace physics
    {
        class RigidBodyListener
        {
            public:

                RigidBodyListener();

                virtual ~RigidBodyListener();

                virtual void onRigidBodyUpdated() = 0;

            protected:

            private:
        };
    }
}

#endif // RIGIDBODYLISTENER_H
