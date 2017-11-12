
#include "SdlApplication.h"
#include "InternalException.h"

namespace application
{
    namespace sdl
    {

        SdlApplication::SdlApplication(const std::string& title, const std::string& icon, const unsigned int& argumentCount, const char* const arguments[]):
            application::GenericApplication(title, argumentCount, arguments),
            m_width(800u),
            m_height(600u),
            m_title(title),
            m_icon(icon),
            m_framerate(60.0),
            m_frameDuration(1000.0 / m_framerate),
            m_screen(nullptr),
            m_processing(false),
            m_listeners()
        {
            // Register options.
            addOption(core::application::ProgramOptions("-width", true));
            addOption(core::application::ProgramOptions("-height", true));
            addOption(core::application::ProgramOptions("-fps"));
        }

        SdlApplication::~SdlApplication()
        {
            SDL_Quit();
        }

        const std::string& SdlApplication::getTitle() const
        {
            return m_title;
        }

        const std::string& SdlApplication::getIcon() const
        {
            return m_icon;
        }

        void SdlApplication::addListener(EventListener* listener)
        {
            m_listeners.push_back(listener);
        }

        void SdlApplication::addDrawable(Drawable* drawable)
        {
            m_drawables.push_back(drawable);
        }

        //==========

        void SdlApplication::doProcess()
        {
            // Retrieve options.
            m_width = getOption("-width").getValueAs<unsigned int>();
            m_height = getOption("-height").getValueAs<unsigned int>();
            const core::application::ProgramOptions& fpsOption(getOption("-fps"));
            if (fpsOption.isFilled())
            {
                m_framerate = fpsOption.getValueAs<double>();
                m_frameDuration = 1000.0 / m_framerate;
            }
            // Create the window.
            createWindow();
            // Perform rendering.
            performRendering();
        }

        //==========

        void SdlApplication::createWindow()
        {
            int initializationStatus(SDL_Init(SDL_INIT_VIDEO));
            if (initializationStatus != 0) {
                throw core::exceptions::InternalException("Could not properly initialize sdl rendering context, window not created.");
            }
			m_screen = SDL_SetVideoMode(m_width, m_height, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
			SDL_FillRect(m_screen, nullptr, SDL_MapRGB(m_screen->format, 255, 255, 255));
			if (m_screen == nullptr) {
				std::string errorMessage("Could not create sdl window: ");
				errorMessage += SDL_GetError();
				throw core::exceptions::InternalException(errorMessage.c_str());
			}
			SDL_Surface* iconAsSurface(SDL_LoadBMP(m_icon.c_str()));
            SDL_WM_SetIcon(iconAsSurface, nullptr);
			SDL_WM_SetCaption(m_title.c_str(), nullptr);
		}

		void SdlApplication::performRendering()
		{
		    m_processing = true;
			do
            {
                events();
				render();
			}
			while (m_processing);
		}

		void SdlApplication::events()
		{
            bool stillEventsInQueue(true);
            while (stillEventsInQueue) {
                // Retrieve a single event
                SDL_Event currentEvent;
                int retValue(SDL_PollEvent(&currentEvent));
                // Check if we need to process this event
                if (!retValue) {
                    // No more events
                    stillEventsInQueue = false;
                }
                else {
                    try {
                        processSingleEvent(currentEvent);
                    }
                    catch (core::exceptions::InternalException& e) {
                        std::cerr << "[ERROR] Unknown exception during event processing: \"" << e.what() << "\"." << std::endl;
                    }
                }
            }
		}

		void SdlApplication::processSingleEvent(const SDL_Event& event)
		{
            switch (event.type) {
            case SDL_QUIT:
                processExitEvent(event);
                break;
            case SDL_KEYDOWN:
                processKeyPressedEvent(event);
                break;
            case SDL_KEYUP:
                processKeyReleasedEvent(event);
                break;
            case SDL_MOUSEMOTION:
                processMouseMotionEvent(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                processMouseButtonPressedEvent(event);
                break;
            case SDL_MOUSEBUTTONUP:
                processMouseButtonReleasedEvent(event);
                break;
            default:
                // Do nothing
                break;
            }
		}

        void SdlApplication::processExitEvent(const SDL_Event& event)
        {
            m_processing = false;
            for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                listenersIterator != m_listeners.end();
                ++listenersIterator)
            {
                (*listenersIterator)->onExitEvent(event);
            }
        }

        void SdlApplication::processKeyPressedEvent(const SDL_Event& event)
        {
            for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                listenersIterator != m_listeners.end();
                ++listenersIterator)
            {
                (*listenersIterator)->onKeyPressedEvent(event.key);
            }
        }

        void SdlApplication::processKeyReleasedEvent(const SDL_Event& event)
        {
            for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                listenersIterator != m_listeners.end();
                ++listenersIterator)
            {
                (*listenersIterator)->onKeyReleasedEvent(event.key);
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                m_processing = false;
                for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                    listenersIterator != m_listeners.end();
                    ++listenersIterator)
                {
                    (*listenersIterator)->onExitEvent(event);
                }
            }
        }

        void SdlApplication::processMouseMotionEvent(const SDL_Event& event)
        {
            for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                listenersIterator != m_listeners.end();
                ++listenersIterator)
            {
                (*listenersIterator)->onMouseMotionEvent(event.motion);
            }
        }

        void SdlApplication::processMouseButtonPressedEvent(const SDL_Event& event)
        {
            if (event.button.button != SDL_BUTTON_WHEELDOWN &&
                event.button.button != SDL_BUTTON_WHEELUP)
            {
                for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                    listenersIterator != m_listeners.end();
                    ++listenersIterator)
                {
                    (*listenersIterator)->onMouseButtonPressedEvent(event.button);
                }
            }
        }

        void SdlApplication::processMouseButtonReleasedEvent(const SDL_Event& event)
        {
            // Check for wheel event.
            if (event.button.button == SDL_BUTTON_WHEELDOWN ||
                event.button.button == SDL_BUTTON_WHEELUP)
            {
                processMouseWheelEvent(event.button.button == SDL_BUTTON_WHEELUP);
            }
            else
            {
                for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                    listenersIterator != m_listeners.end();
                    ++listenersIterator)
                {
                    (*listenersIterator)->onMouseButtonReleasedEvent(event.button);
                }
            }
        }

        void SdlApplication::processMouseWheelEvent(bool upwheel)
        {
            for (std::vector<EventListener*>::iterator listenersIterator = m_listeners.begin();
                listenersIterator != m_listeners.end();
                ++listenersIterator)
            {
                (*listenersIterator)->onMouseWheelEvent(upwheel);
            }
        }

		void SdlApplication::render()
		{
			const unsigned int startingRenderingTime(SDL_GetTicks());
			renderDrawables();
            SDL_Flip(m_screen);
			const unsigned int renderingDuration(SDL_GetTicks() - startingRenderingTime);
			if (renderingDuration > m_frameDuration)
            {
				std::cerr << "[APP] Frame took " << renderingDuration << "ms which is greater than the " << m_frameDuration << "ms authorized to maintain " << m_framerate << "fps" << std::endl;
			}
			else
            {
				const unsigned int remainingDuration(m_frameDuration - renderingDuration);
				if (remainingDuration > 3u)
				{
					SDL_Delay(remainingDuration);
				}
			}
		}

		void SdlApplication::renderDrawables()
		{
            //std::cout << "[APPLICATION] Rendering " << m_drawables.size() << " drawables (" << m_framerate << " fps)" << std::endl;
            for (std::vector<Drawable*>::iterator drawablesIterator = m_drawables.begin() ;
                 drawablesIterator != m_drawables.end() ;
                 ++drawablesIterator)
            {
                Drawable* drawable(*drawablesIterator);
                if (drawable->hasChanged())
                {
                    SDL_Surface* picture = drawable->draw();
                    // Draw the picture
                    utils::sdl::Area render = drawable->getRenderingArea();
                    SDL_Rect dstArea;
                    dstArea.x = static_cast<short int>(render.getX());
                    dstArea.y = static_cast<short int>(render.getY());
                    dstArea.w = static_cast<short int>(render.getWidth());
                    dstArea.h = static_cast<short int>(render.getHeight());
                    drawSurface(picture, nullptr, &dstArea);
                }
            }
		}

        void SdlApplication::drawSurface(SDL_Surface* surface, SDL_Rect* sourceArea, SDL_Rect* destinationArea) {
            if (surface != nullptr)
            {
                SDL_BlitSurface(surface, sourceArea, m_screen, destinationArea);
            }
        }
    }
}
