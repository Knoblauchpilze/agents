#ifndef    RENDERER_HH
# define   RENDERER_HH

# include <memory>
# include "Component.hh"
# include "MovingObject.hh"
# include "olcEngine.hh"
# include "CoordinateFrame.hh"

namespace mas {
  namespace environment {

    class Renderer: public Component {
      public:

        /**
         * @brief - Create a new renderer with the specified moving
         *          object.
         */
        Renderer(const MovingObject& obj);

        /**
         * @brief - Implementation of the interface method to handle
         *          the update of this component with the underlying
         *          data.
         */
        void
        update() override;

        /**
         * @brief - Perform the rendering of this component using
         *          the input engine.
         * @param pge - the engine to use to perform the rendering.
         * @param cf - the coordinate frame allowing to convert the
         *             internal positions to pixel coordinates.
         */
        void
        draw(olc::PixelGameEngine* pge,
             const pge::CoordinateFrame& cf) const noexcept;

      private:

        /**
         * @brief - The moving object attached to this renderer.
         */
        const MovingObject& m_obj;

        /**
         * @brief - The color for this renderer.
         */
        olc::Pixel m_color;
    };

  }
}

#endif    /* RENDERER_HH */
