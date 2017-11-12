#ifndef ENVIRONMENTALOBJECTDRAWER_H
#define ENVIRONMENTALOBJECTDRAWER_H

#include "Drawable.h"
#include <memory>
#include "EnvironmentalObject.h"
#include "EnvironmentalObjectListener.h"

namespace environment
{
    namespace objects
    {
        namespace drawable
        {
            class EnvironmentalObjectDrawer: public application::sdl::Drawable, public environment::objects::EnvironmentalObjectListener
            {
                public:

                    EnvironmentalObjectDrawer(const environment::objects::EnvironmentalObject& object,
                                              const unsigned int& width = 10u,
                                              const unsigned int& height = 10u,
                                              const Uint8& alpha = SDL_ALPHA_OPAQUE / 2);

                    virtual ~EnvironmentalObjectDrawer();

                    void setColor(const SDL_Color& color);

                    void setTransparent(bool transparent);

                    void setRenderingDimensions(const unsigned int& width, const unsigned int& height);

                    virtual void onObjectChanged(const EnvironmentalObject& object);

                    virtual bool hasChanged();

                    virtual utils::sdl::Area getRenderingArea();

                    virtual SDL_Surface* draw();

                protected:

                    virtual SDL_Surface* performAdditionalRendering(SDL_Surface* picture,
                                                                    const utils::sdl::Area& sourceArea,
                                                                    const double& xScale,
                                                                    const double& yScale,
                                                                    const Uint8& alpha);

                    SDL_Surface* createSurface(const unsigned int& width, const unsigned int& height, const SDL_Color& color) const;

                    void onObjectChangedPrivate();

                private:

                    void performRendering();

                private:
                    utils::sdl::Area m_area;

                    bool m_dirty;
                    unsigned int m_width;
                    unsigned int m_height;
                    SDL_Color m_color;
                    SDL_Surface* m_cachedRendering;
            };

            using EnvironmentalObjectDrawerShPtr = std::shared_ptr<EnvironmentalObjectDrawer>;
        }
    }
}

#endif // ENVIRONMENTALOBJECTDRAWER_H
