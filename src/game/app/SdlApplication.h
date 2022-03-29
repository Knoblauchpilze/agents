#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H

#include <iostream>
#include <SDL/SDL.h>
#include "GenericApplication.h"
#include "SdlEventListener.h"
#include "Drawable.h"

namespace application
{
    namespace sdl
    {

        class SdlApplication : public application::GenericApplication
        {
            public:

                SdlApplication(const std::string& title, const std::string& icon, const unsigned int& argumentCount, const char* const arguments[]);

                virtual ~SdlApplication();

                const std::string& getTitle() const;

                const std::string& getIcon() const;

				void addListener(EventListener* listener);

                void addDrawable(Drawable* drawable);

            protected:

                virtual void doProcess();

            private:

                void createWindow();

                void performRendering();

                void events();

                void processSingleEvent(const SDL_Event& event);

				void processExitEvent(const SDL_Event& event);

				void processKeyPressedEvent(const SDL_Event& event);

				void processKeyReleasedEvent(const SDL_Event& event);

				void processMouseMotionEvent(const SDL_Event& event);

				void processMouseButtonPressedEvent(const SDL_Event& event);

				void processMouseButtonReleasedEvent(const SDL_Event& event);

				void processMouseWheelEvent(bool upwheel);

                void render();

                void renderDrawables();

                void drawSurface(SDL_Surface* surface, SDL_Rect* sourceArea, SDL_Rect* destinationArea);

            private:

                unsigned int m_width;
                unsigned int m_height;
                std::string m_title;
                std::string m_icon;
                double m_framerate;
                double m_frameDuration;
                SDL_Surface* m_screen;
                bool m_processing;
				std::vector<EventListener*> m_listeners;
                std::vector<Drawable*> m_drawables;
        };
    }
}

#endif // SDLAPPLICATION_H
