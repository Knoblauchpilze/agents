
#include "SdlEventListener.h"

namespace application
{
    namespace sdl
    {
        EventListener::EventListener()
        {
            // Nothing to do.
        }

        EventListener::~EventListener()
        {
            // Nothing to do.
        }

        void EventListener::onExitEvent(const SDL_Event&)
        {
            // Do nothing.
        }

        void EventListener::onKeyPressedEvent(const SDL_KeyboardEvent&)
        {
            // Do nothing.
        }

        void EventListener::onKeyReleasedEvent(const SDL_KeyboardEvent&)
        {
            // Do nothing.
        }

        void EventListener::onMouseMotionEvent(const SDL_MouseMotionEvent&)
        {
            // Do nothing.
        }

        void EventListener::onMouseButtonPressedEvent(const SDL_MouseButtonEvent&)
        {
            // Do nothing.
        }

        void EventListener::onMouseButtonReleasedEvent(const SDL_MouseButtonEvent&)
        {
            // Do nothing.
        }

        void EventListener::onMouseWheelEvent(bool)
        {
            // Do nothing.
        }
    }
}
