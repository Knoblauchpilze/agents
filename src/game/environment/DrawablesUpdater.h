#ifndef DRAWABLESUPDATER_H
#define DRAWABLESUPDATER_H

#include "SdlEventListener.h"
#include "EnvironmentalObjectDrawer.h"
#include "BodyDrawer.h"

namespace environment
{
    namespace drawable
    {
        class DrawableUpdater: public application::sdl::EventListener
        {
            public:

                DrawableUpdater();

                virtual ~DrawableUpdater();

                void registerObjectDrawable(environment::objects::drawable::EnvironmentalObjectDrawerShPtr drawable);

                void registerBodyDrawable(environment::objects::drawable::BodyDrawerShPtr drawable);

                virtual void onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent);

            private:

                void handleFrustumActivation();

                void handleTransparencyActivation();

            private:

                std::vector<environment::objects::drawable::EnvironmentalObjectDrawerShPtr> m_objectsDrawables;
                std::vector<environment::objects::drawable::BodyDrawerShPtr> m_bodiesDrawables;

                bool m_frustumDisplayed;
                bool m_transparencyActivated;
        };
    }
}

#endif // DRAWABLESUPDATER_H
