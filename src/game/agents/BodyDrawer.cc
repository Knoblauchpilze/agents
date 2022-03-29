
#include "BodyDrawer.h"

namespace environment
{
    namespace objects
    {
        namespace drawable
        {
            BodyDrawer::BodyDrawer(const environment::objects::Body& body, bool frustum):
                EnvironmentalObjectDrawer(body),
                m_frustumDisplay(frustum),
                m_area(body.getFrustum().asArea()),
                m_frustumColor({255, 255, 255, SDL_ALPHA_OPAQUE})
            {
                // Nothing to do.
            }

            BodyDrawer::~BodyDrawer()
            {
                // Nothing to do.
            }

            void BodyDrawer::setDisplayFrustum(bool display)
            {
                lock();
                m_frustumDisplay = display;
                onObjectChangedPrivate();
                unlock();
            }

            void BodyDrawer::setFrustumDisplayColor(const SDL_Color& color)
            {
                lock();
                m_frustumColor = color;
                onObjectChangedPrivate();
                unlock();
            }

            void BodyDrawer::onObjectChanged(const environment::objects::Body& object)
            {
                lock();
                m_area = object.getFrustum().asArea();
                unlock();
                EnvironmentalObjectDrawer::onObjectChanged(object);
            }

            SDL_Surface* BodyDrawer::performAdditionalRendering(SDL_Surface* picture, const utils::sdl::Area& sourceArea, const double& xScale, const double& yScale, const Uint8& alpha)
            {
                if (!m_frustumDisplay)
                {
                    return picture;
                }
                else
                {
                    // Create a surface with the correct height, not transparent (so that we keep the transparency level of the original surface)
                    // and with another colour so that we can make it completely transparent (the colour).
                    const unsigned int frustumRenderingWidth(static_cast<unsigned int>(xScale * m_area.getWidth()));
                    const unsigned int frustumRenderingHeight(static_cast<unsigned int>(yScale * m_area.getHeight()));
                    const SDL_Color otherColor({0, 0, 0, alpha});
                    SDL_Surface* backgroundSurface(createSurface(frustumRenderingWidth, frustumRenderingHeight, otherColor));
                    SDL_SetColorKey(backgroundSurface, SDL_FALSE, SDL_MapRGB(backgroundSurface->format, otherColor.r, otherColor.g, otherColor.b));

                    const double xCenterToFrustum((m_area.getWidth() -  sourceArea.getWidth()) / 2.0);
                    const double yCenterToFrustum((m_area.getHeight() -  sourceArea.getHeight()) / 2.0);
                    const short int xOffset(static_cast<short int>(xCenterToFrustum * xScale));
                    const short int yOffset(static_cast<short int>(yCenterToFrustum * yScale));

                    // Create the frustum representation.
                    SDL_Surface* frustumSurface(createSurface(frustumRenderingWidth, frustumRenderingHeight, m_frustumColor));
                    // We need to render only parts which do not overlap the initial body so as not to modify its colour if it is transparent.
                    SDL_Rect srcArea({0, 0, static_cast<std::uint16_t>(frustumRenderingWidth), static_cast<std::uint16_t>(yOffset)});
                    SDL_Rect dstArea({0, 0, static_cast<std::uint16_t>(frustumRenderingWidth), static_cast<std::uint16_t>(frustumRenderingHeight)});
                    SDL_BlitSurface(frustumSurface, &srcArea, backgroundSurface, &dstArea);

                    srcArea = {0, 0, static_cast<std::uint16_t>(frustumRenderingWidth), static_cast<std::uint16_t>(yOffset)};
                    dstArea = {0, static_cast<std::int16_t>(frustumRenderingHeight - yOffset), static_cast<std::uint16_t>(frustumRenderingWidth), static_cast<std::uint16_t>(frustumRenderingHeight)};
                    SDL_BlitSurface(frustumSurface, &srcArea, backgroundSurface, &dstArea);

                    srcArea = {0, 0, static_cast<std::uint16_t>(xOffset), static_cast<std::uint16_t>(frustumRenderingHeight - 2 * yOffset)};
                    dstArea = {0, static_cast<std::int16_t>(yOffset), static_cast<std::uint16_t>(frustumRenderingWidth), static_cast<std::uint16_t>(frustumRenderingHeight)};
                    SDL_BlitSurface(frustumSurface, &srcArea, backgroundSurface, &dstArea);

                    srcArea = {0, 0, static_cast<std::uint16_t>(xOffset), static_cast<std::uint16_t>(frustumRenderingHeight - 2 * yOffset)};
                    dstArea = {static_cast<std::int16_t>(frustumRenderingWidth - xOffset), static_cast<std::int16_t>(yOffset), static_cast<std::uint16_t>(frustumRenderingWidth), static_cast<std::uint16_t>(frustumRenderingHeight)};
                    SDL_BlitSurface(frustumSurface, &srcArea, backgroundSurface, &dstArea);

                    // Render the input surface onto this buffer surface.
                    dstArea.x = xOffset;
                    dstArea.y = yOffset;
                    SDL_BlitSurface(picture, nullptr, backgroundSurface, &dstArea);

                    // Release memory.
                    SDL_FreeSurface(frustumSurface);
                    SDL_FreeSurface(picture);

                    return backgroundSurface;
                }
            }
        }
    }
}
