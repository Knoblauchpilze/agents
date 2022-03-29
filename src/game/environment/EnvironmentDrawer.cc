
#include "EnvironmentDrawer.h"
#include "ComparisonUtils.h"

namespace environment
{
    namespace drawable
    {
        const double EnvironmentDrawer::sk_maximumNumberOfHorizontalGridLines(10.0);
        const double EnvironmentDrawer::sk_maximumNumberOfVerticalGridLines(10.0);
        const double EnvironmentDrawer::sk_minimumNumberOfHorizontalGridLines(1.0);
        const double EnvironmentDrawer::sk_minimumNumberOfVerticalGridLines(1.0);
        const double EnvironmentDrawer::sk_gridSpacingUpdateFactor(10.0);

        EnvironmentDrawer::EnvironmentDrawer(const Environment& environment, const utils::sdl::Area& source, const utils::sdl::Area& rendering):
            application::sdl::Drawable(),
            application::sdl::EventListener(),
            environment::listener::EnvironmentListener(),
            m_environment(environment),
            m_sourceArea(source),
            m_renderingArea(rendering),
            m_dirty(true),
            m_cachedRendering(nullptr),
            m_clicking(false),
            m_oldX(rendering.getX() + rendering.getWidth() / 2.0),
            m_oldY(rendering.getY() + rendering.getHeight() / 2.0),
            m_gridVisible(false),
            m_gridXStep(1.0),
            m_gridYStep(1.0)
        {
            // Nothing to do.
        }

        EnvironmentDrawer::~EnvironmentDrawer()
        {
            if (m_cachedRendering != nullptr)
            {
                SDL_FreeSurface(m_cachedRendering);
            }
        }

        utils::sdl::Area EnvironmentDrawer::getRenderingArea()
        {
            lock();
            utils::sdl::Area copyOfRenderingArea(m_renderingArea);
            unlock();
            return copyOfRenderingArea;
        }

        void EnvironmentDrawer::setRenderingArea(const utils::sdl::Area& area)
        {
            lock();
            m_renderingArea = area;
            unlock();
        }

        void EnvironmentDrawer::moveRenderingArea(const double& x, const double& y)
        {
            lock();
            m_sourceArea.setX(m_sourceArea.getX() + x);
            m_sourceArea.setY(m_sourceArea.getY() + y);
            m_dirty = true;
            unlock();
        }

        bool EnvironmentDrawer::hasChanged()
        {
            lock();
            bool dirty(m_dirty);
            unlock();
            return dirty;
        }

        SDL_Surface* EnvironmentDrawer::draw()
        {
            lock();
            if (m_dirty)
            {
                performRendering();
                m_dirty = false;
            }
            unlock();
            return m_cachedRendering;
        }

        void EnvironmentDrawer::onEnvironmentUpdate()
        {
            lock();
            m_dirty = true;
            unlock();
        }

        void EnvironmentDrawer::onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent)
        {
            if (keyEvent.keysym.sym == SDLK_LEFT)
            {
                moveRenderingArea(-0.01, 0.0);
            }
            else if (keyEvent.keysym.sym == SDLK_RIGHT)
            {
                moveRenderingArea(0.01, 0.0);
            }
            else if (keyEvent.keysym.sym == SDLK_DOWN)
            {
                moveRenderingArea(0.0, -0.01);
            }
            else if (keyEvent.keysym.sym == SDLK_UP)
            {
                moveRenderingArea(0.0, 0.01);
            }
            else if (keyEvent.keysym.sym == SDLK_g)
            {
                toggleGridDisplay();
            }
            else
            {
                // Do nothing.
            }
        }

        void EnvironmentDrawer::onKeyPressedEvent(const SDL_KeyboardEvent& /*keyEvent*/)
        {
        }

        void EnvironmentDrawer::onMouseMotionEvent(const SDL_MouseMotionEvent& mouseMotionEvent)
        {
            lock();
            bool copyOfClick(m_clicking);
            unlock();
            if (copyOfClick)
            {
                // We need to translate the rendering area associated to the drawer. Basically what would be nice is to fix the position under the cursor when the user clicked, and to make it
                // follow the current position of the mouse. This enables to have a 'grab' metaphor where the user click on a specific position and then move this position around.
                // Convert the last mouse position in environment coordinate frame
                double xWorldOld(0.0), yWorldOld(0.0);
                convertScreenCoordinatesToEnvironmentCoordinates(m_oldX, m_oldY, xWorldOld, yWorldOld);
                double xWorld(0.0), yWorld(0.0);
                convertScreenCoordinatesToEnvironmentCoordinates(mouseMotionEvent.x, mouseMotionEvent.y, xWorld, yWorld);

                const double xTranslation(xWorldOld - xWorld);
                const double yTranslation(yWorldOld - yWorld);
                // Translate the window
                moveRenderingArea(xTranslation, yTranslation);
            }

            // Prepare to the next frame either clic or zoom).
            lock();
            m_oldX = mouseMotionEvent.x;
            m_oldY = mouseMotionEvent.y;
            unlock();
        }

        void EnvironmentDrawer::onMouseButtonPressedEvent(const SDL_MouseButtonEvent& mouseButtonEvent)
        {
            bool changed(m_clicking);
            m_clicking = (mouseButtonEvent.button == SDL_BUTTON_LEFT ? true : m_clicking);
            changed = (m_clicking != changed);
            if (changed)
            {
                m_oldX = mouseButtonEvent.x;
                m_oldY = mouseButtonEvent.y;
            }
        }

        void EnvironmentDrawer::onMouseButtonReleasedEvent(const SDL_MouseButtonEvent& mouseButtonEvent)
        {
            m_clicking = (mouseButtonEvent.button == SDL_BUTTON_LEFT ? false : m_clicking);
        }

        void EnvironmentDrawer::onMouseWheelEvent(bool upwheel)
        {
            // Compute the zoom to apply based on the wheel event.
			const double zoomFactor(1.2);
			double zoomToApply(1.0);
			// Check if we should zoom in or out
			if (upwheel) {
				zoomToApply /= zoomFactor;
			}
			else {
				zoomToApply *= zoomFactor;
			}
			// Convert the position into environment coordinates
			double xWorld(0.0), yWorld(0.0);
			convertScreenCoordinatesToEnvironmentCoordinates(m_oldX, m_oldY, xWorld, yWorld);
			// What we want can be described as follows: we want the zoom to keep the input position constant, so that the user can still zoom on this particular point if he wants.
			// In addition it enables to keep the point of interest in the view, which is usually what we want (because if the user wants to zoom on this point, we might assume
            // that he still wants it in the viewport when the zoom is done).
			// So we need to guarantee that the position of the point described at 'position' stays constant after applying the zoom.
			// Obtain a copy of the drawing and rendering area
			lock();
			const utils::sdl::Area copyOfSourceArea(m_sourceArea);
			const utils::sdl::Area copyOfRenderingArea(m_renderingArea);
			unlock();
			// First, compute the new dimensions of the drawing area.
			const double newDrawingWidth(copyOfSourceArea.getWidth() * zoomToApply);
			const double newDrawingHeight(copyOfSourceArea.getHeight() * zoomToApply);
			// Compute the vector joining the old center and this fixed position
			double xCenterToFixedPoint(copyOfSourceArea.getX() - xWorld);
			double yCenterToFixedPoint(copyOfSourceArea.getY() - yWorld);
			// This vector needs to be scaled so that it matches the new dimensions
			xCenterToFixedPoint *= zoomToApply;
			yCenterToFixedPoint *= zoomToApply;
			// Now we can compute the new center in the environment's coordinate frame
			const double newXDrawingCenter(xWorld + xCenterToFixedPoint);
			const double newYDrawingCenter(yWorld + yCenterToFixedPoint);
			// Update the drawing area
			lock();
			m_sourceArea.setX(newXDrawingCenter);
			m_sourceArea.setY(newYDrawingCenter);
			m_sourceArea.setWidth(newDrawingWidth);
			m_sourceArea.setHeight(newDrawingHeight);
			m_dirty = true;
			// And update grid step.
			updateGridStep();
			unlock();
        }

        void EnvironmentDrawer::performRendering()
        {
            // Create the background surface.
            createBackgroundSurface({0, 0, 0, SDL_ALPHA_OPAQUE});
            // Display the grid if needed.
            if (m_gridVisible)
            {
                displayGrid({255, 255, 0, SDL_ALPHA_OPAQUE}, m_gridXStep, m_gridYStep);
            }

            const std::vector<objects::drawable::EnvironmentalObjectDrawerShPtr>& drawables(m_environment.getDrawables());
            const double xScale(m_renderingArea.getWidth() / m_sourceArea.getWidth());
            const double yScale(m_renderingArea.getHeight() / m_sourceArea.getHeight());
            const double& xDrawingOrigin(m_sourceArea.getLeftBound());
            const double& yDrawingOrigin(m_sourceArea.getBottomBound());
            const double& drawingHeight(m_sourceArea.getHeight());

            for (std::vector<objects::drawable::EnvironmentalObjectDrawerShPtr>::const_iterator drawablesIterator = drawables.cbegin() ;
                 drawablesIterator != drawables.cend() ;
                 ++drawablesIterator)
            {
                objects::drawable::EnvironmentalObjectDrawer& drawable(**drawablesIterator);

                const utils::sdl::Area& drawableArea(drawable.getRenderingArea());
                if (drawableArea.intersects(m_sourceArea))
                {
                    const double xObject(drawableArea.getLeftBound() - xDrawingOrigin);
                    const double yObject(yDrawingOrigin + drawingHeight - drawableArea.getTopBound());

                    SDL_Rect dstArea;
                    dstArea.x = static_cast<short int>(xScale * xObject);
                    dstArea.y = static_cast<short int>(yScale * yObject);
                    dstArea.w = static_cast<short int>(xScale * drawableArea.getWidth());
                    dstArea.h = static_cast<short int>(yScale * drawableArea.getHeight());

                    drawable.setRenderingDimensions(dstArea.w, dstArea.h);
                    SDL_Surface* objectSurface(drawable.draw());

                    // Make sure that rendering dimensions have been respected.
                    if (objectSurface->w > dstArea.w)
                    {
                        dstArea.x = dstArea.x - (objectSurface->h - dstArea.w) / 2;
                        dstArea.w = objectSurface->w;
                    }
                    if (objectSurface->h > dstArea.h)
                    {
                        dstArea.y = dstArea.y - (objectSurface->h - dstArea.h) / 2;
                        dstArea.h = objectSurface->h;
                    }

                    SDL_BlitSurface(objectSurface, nullptr, m_cachedRendering, &dstArea);
                }
            }
        }

        void EnvironmentDrawer::clearBackgroundSurface()
        {
            if (m_cachedRendering != nullptr)
            {
                SDL_FreeSurface(m_cachedRendering);
                m_cachedRendering = nullptr;
            }
        }

        void EnvironmentDrawer::createBackgroundSurface(const SDL_Color& color)
        {
            if (m_cachedRendering)
            {
                const bool widthVaried(!utils::comparison::doubleEqual(1.0 * m_cachedRendering->w, m_renderingArea.getWidth()));
                const bool heightVaried(!utils::comparison::doubleEqual(1.0 * m_cachedRendering->h, m_renderingArea.getHeight()));
                if (widthVaried || heightVaried)
                {
                    clearBackgroundSurface();
                }
            }
            if (m_cachedRendering)
            {
                SDL_FillRect(m_cachedRendering, nullptr, SDL_MapRGB(m_cachedRendering->format, color.r, color.g, color.b));
            }
            else
            {
                m_cachedRendering = createSurface(m_renderingArea.getWidth(), m_renderingArea.getHeight(), color);
            }
        }

        SDL_Surface* EnvironmentDrawer::createSurface(const unsigned int& width, const unsigned int& height, const SDL_Color& color)
        {
            SDL_Surface* surface(SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0));
            SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, color.r, color.g, color.b));
            SDL_SetAlpha(surface, SDL_SRCALPHA, color.unused);
            return surface;
        }

        void EnvironmentDrawer::convertScreenCoordinatesToEnvironmentCoordinates(const Uint16& xScreen, const Uint16& yScreen, double& xWorld, double& yWorld)
        {
            // Retrieve and copy the drawing area and rendering area.
			lock();
			utils::sdl::Area copyOfSourceArea(m_sourceArea);
			utils::sdl::Area copyOfRenderingArea(m_renderingArea);
			unlock();
			// The 'm_rendering' area represents a 'screen' area, which means that its center is not given by 'getX(), getY()' as for the m_drawing area, but needs to be computed.
			// This is required to obtain the position of the screen relatively to the center of view.
			const double xDrawerScreenCenter(copyOfRenderingArea.getX() + copyOfRenderingArea.getWidth() / 2.0);
			const double yDrawerScreenCenter(copyOfRenderingArea.getY() + copyOfRenderingArea.getHeight() / 2.0);
			// Convert the screen coordinates into local drawer rendering coordinates: we need to handle the flipped y axis on screen
			const double xDrawerScreenCoordinates(xScreen - xDrawerScreenCenter);
			const double yDrawerScreenCoordinates(yDrawerScreenCenter - yScreen);
			// Convert the local drawer coordinates into environment coordinates
			const double xRatioDrawerToEnvironment(copyOfSourceArea.getWidth() / copyOfRenderingArea.getWidth());
			const double yRatioDrawerToEnvironment(copyOfSourceArea.getHeight() / copyOfRenderingArea.getHeight());
			double xEnvironment(xDrawerScreenCoordinates * xRatioDrawerToEnvironment);
			double yEnvironment(yDrawerScreenCoordinates * yRatioDrawerToEnvironment);
			// Offset with the position of the drawing area
			xEnvironment += copyOfSourceArea.getX();
			yEnvironment += copyOfSourceArea.getY();
			// Return the built-in coordinates
			xWorld = xEnvironment;
			yWorld = yEnvironment;
		}

		void EnvironmentDrawer::toggleGridDisplay()
		{
            lock();
            m_gridVisible = !m_gridVisible;
            if (m_gridVisible)
            {
                updateGridStep();
            }
            unlock();
		}

		void EnvironmentDrawer::displayGrid(const SDL_Color& color, const double& xStep, const double& yStep)
		{
		    // Create grid surfaces.
		    SDL_Surface* verticalGridLine(createSurface(1u, m_renderingArea.getHeight(), color));
		    SDL_Surface* horizontalGridLine(createSurface(m_renderingArea.getWidth(), 1u, color));
		    SDL_Surface* redAxis(createSurface(m_renderingArea.getWidth(), 1u, {255, 0, 0, SDL_ALPHA_OPAQUE}));
		    SDL_Surface* greenAxis(createSurface(1u, m_renderingArea.getHeight(), {0, 255, 0, SDL_ALPHA_OPAQUE}));
            // Display grid lines according to the step.
            const double& xDrawingOrigin(m_sourceArea.getLeftBound());
            const double& yDrawingOrigin(m_sourceArea.getBottomBound());
            const double& drawingHeight(m_renderingArea.getHeight());

            const double xFirstLine(std::floor(m_sourceArea.getLeftBound() / xStep) * xStep);
            const double yFirstLine(std::floor(m_sourceArea.getBottomBound() / yStep) * yStep);
            const double xScale(m_renderingArea.getWidth() / m_sourceArea.getWidth());
            const double yScale(m_renderingArea.getHeight() / m_sourceArea.getHeight());

            // Perform the rendering of each horizontal line.
            SDL_Rect dstArea;
            int indexHorizontalLine(0);
            double yHorizontalLine(yFirstLine);
            while (yHorizontalLine < m_sourceArea.getTopBound())
            {
                yHorizontalLine = yFirstLine + indexHorizontalLine * yStep;
                const unsigned int yPixelLine(drawingHeight - (yHorizontalLine - yDrawingOrigin) * yScale);
                dstArea.x = 0;
                dstArea.y = static_cast<short int>(yPixelLine);
                if (utils::comparison::doubleEqual(yHorizontalLine, 0.0))
                {
                    SDL_BlitSurface(redAxis, nullptr, m_cachedRendering, &dstArea);
                }
                else
                {
                    SDL_BlitSurface(horizontalGridLine, nullptr, m_cachedRendering, &dstArea);
                }
                ++indexHorizontalLine;
            }
            // Perform the rendering of each vertical line.
            int indexVerticalLine(0);
            double xVerticalLine(xFirstLine);
            while (xVerticalLine < m_sourceArea.getRightBound())
            {
                xVerticalLine = xFirstLine + indexVerticalLine * xStep;
                const unsigned int xPixelLine((xVerticalLine - xDrawingOrigin) * xScale);
                dstArea.x = static_cast<short int>(xPixelLine);
                dstArea.y = 0;
                if (utils::comparison::doubleEqual(xVerticalLine, 0.0))
                {
                    SDL_BlitSurface(greenAxis, nullptr, m_cachedRendering, &dstArea);
                }
                else
                {
                    SDL_BlitSurface(verticalGridLine, nullptr, m_cachedRendering, &dstArea);
                }

                ++indexVerticalLine;
            }

		    // Release memory.
		    SDL_FreeSurface(verticalGridLine);
		    SDL_FreeSurface(horizontalGridLine);
		    SDL_FreeSurface(redAxis);
		    SDL_FreeSurface(greenAxis);
		}

		void EnvironmentDrawer::updateGridStep()
		{
		    // We do not want to draw more than 10 lines to represent the grid.
		    const double numberOfHorizontalLines(m_sourceArea.getWidth() / m_gridXStep);
		    const double numberOfVerticalLines(m_sourceArea.getHeight() / m_gridYStep);
		    if (numberOfHorizontalLines > sk_maximumNumberOfHorizontalGridLines)
            {
                m_gridXStep *= sk_gridSpacingUpdateFactor;
            }
            else if (numberOfHorizontalLines < sk_minimumNumberOfHorizontalGridLines)
            {
                m_gridXStep /= sk_gridSpacingUpdateFactor;
            }
            if (numberOfVerticalLines > sk_maximumNumberOfVerticalGridLines)
            {
                m_gridYStep *= sk_gridSpacingUpdateFactor;
            }
            else if (numberOfVerticalLines < sk_minimumNumberOfVerticalGridLines)
            {
                m_gridYStep /= sk_gridSpacingUpdateFactor;
            }
		}
    }
}
