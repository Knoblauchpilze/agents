
#include "DrawablesUpdater.h"

namespace environment
{
    namespace drawable
    {
        DrawableUpdater::DrawableUpdater():
            application::sdl::EventListener(),
            m_objectsDrawables(),
            m_bodiesDrawables(),
            m_frustumDisplayed(false),
            m_transparencyActivated(true)
        {
            // Nothing to do.
        }

        DrawableUpdater::~DrawableUpdater()
        {
            // Nothing to do.
        }

        void DrawableUpdater::registerObjectDrawable(environment::objects::drawable::EnvironmentalObjectDrawerShPtr drawable)
        {
            m_objectsDrawables.push_back(drawable);
        }

        void DrawableUpdater::registerBodyDrawable(environment::objects::drawable::BodyDrawerShPtr drawable)
        {
            m_bodiesDrawables.push_back(drawable);
        }

        void DrawableUpdater::onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent)
        {
            switch (keyEvent.keysym.sym)
            {
                case SDLK_f:
                    handleFrustumActivation();
                    break;
                case SDLK_t:
                    handleTransparencyActivation();
                    break;
                default:
                    // Do nothing.
                    break;
            }
        }

        //==========

        void DrawableUpdater::handleFrustumActivation()
        {
            // Update the frustum status.
            m_frustumDisplayed = !m_frustumDisplayed;

            using VectorOfBodyDrawerIterator = std::vector<environment::objects::drawable::BodyDrawerShPtr>::iterator;
            for (VectorOfBodyDrawerIterator body = m_bodiesDrawables.begin() ; body != m_bodiesDrawables.end() ; ++body)
            {
                (*body)->setDisplayFrustum(m_frustumDisplayed);
            }
        }

        void DrawableUpdater::handleTransparencyActivation()
        {
            // Update the transparency activation.
            m_transparencyActivated = !m_transparencyActivated;

            using VectorOfObjectDrawerIterator = std::vector<environment::objects::drawable::EnvironmentalObjectDrawerShPtr>::iterator;
            for (VectorOfObjectDrawerIterator object = m_objectsDrawables.begin() ; object != m_objectsDrawables.end() ; ++object)
            {
                (*object)->setTransparent(m_transparencyActivated);
            }
        }
    }
}
