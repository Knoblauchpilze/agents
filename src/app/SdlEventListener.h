#ifndef SDLEVENTLISTENER_H
#define SDLEVENTLISTENER_H

#include <iostream>
#include <SDL.h>

namespace application
{
    namespace sdl
    {
        class EventListener
        {
            public:

                EventListener();

                virtual ~EventListener();

                virtual void onExitEvent(const SDL_Event& exitEvent);

                virtual void onKeyPressedEvent(const SDL_KeyboardEvent& keyEvent);

                virtual void onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent);

                virtual void onMouseMotionEvent(const SDL_MouseMotionEvent& mouseMotionEvent);

                virtual void onMouseButtonPressedEvent(const SDL_MouseButtonEvent& mouseButtonEvent);

                virtual void onMouseButtonReleasedEvent(const SDL_MouseButtonEvent& mouseButtonEvent);

                virtual void onMouseWheelEvent(bool upwheel);

            protected:

            private:
        };
    }
}

#endif // SDLEVENTLISTENER_H
