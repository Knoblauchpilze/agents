#ifndef BODYDRAWER_H
#define BODYDRAWER_H

#include "EnvironmentalObjectDrawer.h"
#include "Body.h"
#include "Frustum.h"

namespace environment
{
    namespace objects
    {
        namespace drawable
        {
            class BodyDrawer: public EnvironmentalObjectDrawer
            {
                public:

                    BodyDrawer(const environment::objects::Body& body, bool frustum = false);

                    virtual ~BodyDrawer();

                    void setDisplayFrustum(bool display);

                    void setFrustumDisplayColor(const SDL_Color& color);

                    virtual void onObjectChanged(const environment::objects::Body& object);

                protected:

                    virtual SDL_Surface* performAdditionalRendering(SDL_Surface* picture,
                                                                    const utils::sdl::Area& sourceArea,
                                                                    const double& xScale,
                                                                    const double& yScale,
                                                                    const Uint8& alpha);

                private:

                    bool m_frustumDisplay;
                    utils::sdl::Area m_area;
                    SDL_Color m_frustumColor;
            };

            using BodyDrawerShPtr = std::shared_ptr<BodyDrawer>;
        }
    }
}

#endif // BODYDRAWER_H
