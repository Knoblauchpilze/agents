#ifndef    RENDERER_HH
# define   RENDERER_HH

# include <memory>
# include "Component.hh"
# include "MovingObject.hh"
# include "olcEngine.hh"
# include "CoordinateFrame.hh"

namespace mas {
  namespace environment {

    /// @brief - The rendering mode for agents.
    enum class RenderingMode {
      Square,
      Circle
    };

    class Renderer: public Component {
      public:

        /**
         * @brief - Create a new renderer with the specified moving
         *          object.
         * @param obj - the object attached to this renderer.
         * @param mode - the rendering mode.
         */
        Renderer(const MovingObject& obj,
                 const RenderingMode& mode);

        /**
         * @brief - Create a new renderer with the specified moving
         *          object and color.
         * @param obj - the object attached to this renderer.
         * @param mode - the rendering mode.
         * @param color - the color of the element.
         */
        Renderer(const MovingObject& obj,
                 const RenderingMode& mode,
                 const olc::Pixel& color);

        /**
         * @brief - Implementation of the interface method to handle
         *          the update of this component with the underlying
         *          data.
         * @param manager - information about the current timestamp.
         */
        void
        simulate(const time::Manager& manager) override;

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
         * @brief - The rendering mode for the attached object.
         */
        RenderingMode m_mode;

        /**
         * @brief - The color for this renderer.
         */
        olc::Pixel m_color;
    };

  }
}

#endif    /* RENDERER_HH */
