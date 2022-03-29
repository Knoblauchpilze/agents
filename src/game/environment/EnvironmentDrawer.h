#ifndef DRAWABLEENVIRONMENT_H
#define DRAWABLEENVIRONMENT_H

#include "Drawable.h"
#include "Environment.h"
#include "EnvironmentalObjectDrawer.h"
#include "EnvironmentListener.h"
#include "SdlEventListener.h"

namespace environment
{
    namespace drawable
    {
        class EnvironmentDrawer: public application::sdl::Drawable, public application::sdl::EventListener, public environment::listener::EnvironmentListener
        {
            public:

                EnvironmentDrawer(const Environment& drawable, const utils::sdl::Area& source, const utils::sdl::Area& rendering);

                ~EnvironmentDrawer();

                virtual utils::sdl::Area getRenderingArea();

                void setRenderingArea(const utils::sdl::Area& area);

                void moveRenderingArea(const double& x, const double& y);

                virtual bool hasChanged();

                virtual SDL_Surface* draw();

                virtual void onEnvironmentUpdate();

                virtual void onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent);

                virtual void onKeyPressedEvent(const SDL_KeyboardEvent& keyEvent);

                virtual void onMouseMotionEvent(const SDL_MouseMotionEvent& mouseMotionEvent);

                virtual void onMouseButtonPressedEvent(const SDL_MouseButtonEvent& mouseButtonEvent);

                virtual void onMouseButtonReleasedEvent(const SDL_MouseButtonEvent& mouseButtonEvent);

                virtual void onMouseWheelEvent(bool upwheel);

            private:

                void performRendering();

                void clearBackgroundSurface();

                void createBackgroundSurface(const SDL_Color& color);

                static SDL_Surface* createSurface(const unsigned int& width, const unsigned int& height, const SDL_Color& color);

                void convertScreenCoordinatesToEnvironmentCoordinates(const Uint16& xScreen, const Uint16& yScreen, double& xWorld, double& yWorld);

                void toggleGridDisplay();

                void displayGrid(const SDL_Color& color, const double& xStep, const double& yStep);

                void updateGridStep();

            private:

                static const double sk_maximumNumberOfHorizontalGridLines;
                static const double sk_maximumNumberOfVerticalGridLines;
                static const double sk_minimumNumberOfHorizontalGridLines;
                static const double sk_minimumNumberOfVerticalGridLines;
                static const double sk_gridSpacingUpdateFactor;

                const Environment& m_environment;
                utils::sdl::Area m_sourceArea;
                utils::sdl::Area m_renderingArea;
                bool m_dirty;
                SDL_Surface* m_cachedRendering;

                bool m_clicking;
                Uint16 m_oldX;
                Uint16 m_oldY;
                bool m_gridVisible;
                double m_gridXStep;
                double m_gridYStep;

        };
    }
}

#endif // DRAWABLEENVIRONMENT_H
