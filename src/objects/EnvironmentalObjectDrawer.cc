
#include "EnvironmentalObjectDrawer.h"

namespace environment
{
    namespace objects
    {
        namespace drawable
        {
            EnvironmentalObjectDrawer::EnvironmentalObjectDrawer(const environment::objects::EnvironmentalObject& object,
                                                                 const unsigned int& width,
                                                                 const unsigned int& height,
                                                                 const Uint8& alpha):
                application::sdl::Drawable(),
                environment::objects::EnvironmentalObjectListener(),
                m_area(object.getBoundingBox().asArea()),
                m_dirty(true),
                m_width(width),
                m_height(height),
                m_color({static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255), alpha}),
                m_cachedRendering(nullptr)
            {
                // Nothing to do.
            }

            EnvironmentalObjectDrawer::~EnvironmentalObjectDrawer()
            {
                // Nothing to do.
            }

            void EnvironmentalObjectDrawer::setColor(const SDL_Color& color)
            {
                lock();
                m_color = color;
                m_dirty = true;
                unlock();
            }

            void EnvironmentalObjectDrawer::setTransparent(bool transparent)
            {
                lock();
                if (transparent && m_color.unused == SDL_ALPHA_OPAQUE)
                {
                    m_color.unused = SDL_ALPHA_OPAQUE / 2;
                    m_dirty = true;
                }
                else if (!transparent && m_color.unused != SDL_ALPHA_OPAQUE)
                {
                    m_color.unused = SDL_ALPHA_OPAQUE;
                    m_dirty = true;
                }
                else
                {
                    // No modifications.
                }
                unlock();
            }

            void EnvironmentalObjectDrawer::setRenderingDimensions(const unsigned int& width, const unsigned int& height)
            {
                lock();
                if (m_width != width)
                {
                    m_width = width;
                    m_dirty = true;
                }
                if (m_height != height)
                {
                    m_height = height;
                    m_dirty = true;
                }
                unlock();
            }

            void EnvironmentalObjectDrawer::onObjectChanged(const EnvironmentalObject& object)
            {
                lock();
                m_area = object.getBoundingBox().asArea();
                onObjectChangedPrivate();
                unlock();
            }

            bool EnvironmentalObjectDrawer::hasChanged()
            {
                lock();
                bool dirty(m_dirty);
                unlock();
                return dirty;
            }

            utils::sdl::Area EnvironmentalObjectDrawer::getRenderingArea()
            {
                lock();
                utils::sdl::Area copyOfRenderingArea(m_area);
                unlock();
                return copyOfRenderingArea;
            }

            SDL_Surface* EnvironmentalObjectDrawer::draw()
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

            SDL_Surface* EnvironmentalObjectDrawer::performAdditionalRendering(SDL_Surface* picture, const utils::sdl::Area&, const double&, const double&, const Uint8&)
            {
                // Return the input picture.
                return picture;
            }

            SDL_Surface* EnvironmentalObjectDrawer::createSurface(const unsigned int& width, const unsigned int& height, const SDL_Color& color) const
            {
                SDL_Surface* picture(SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0));
                SDL_FillRect(picture, nullptr, SDL_MapRGB(picture->format, color.r, color.g, color.b));
                SDL_SetAlpha(picture, SDL_SRCALPHA, color.unused);
                return picture;
            }

            void EnvironmentalObjectDrawer::onObjectChangedPrivate()
            {
                m_dirty = true;
            }

            void EnvironmentalObjectDrawer::performRendering()
            {
                if (m_cachedRendering != nullptr)
                {
                    SDL_FreeSurface(m_cachedRendering);
                    m_cachedRendering = nullptr;
                }
                SDL_Surface* thisRendering(createSurface(m_width, m_height, m_color));
                m_cachedRendering = performAdditionalRendering(thisRendering, m_area, m_width, m_height, m_color.unused);
            }
        }
    }
}
