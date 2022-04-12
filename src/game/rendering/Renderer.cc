
# include "Renderer.hh"
# include <core_utils/RNG.hh>

namespace {

  void
  renderSquare(olc::PixelGameEngine* pge,
               const pge::CoordinateFrame& cf,
               const utils::Boxf& area,
               const olc::Pixel& color) noexcept
  {
    // Convert the position of the area. As it is a
    // centered based area, we need to convert the
    // position of the top left corner.
    float x = area.getTopLeftCorner().x();
    float y = area.getTopLeftCorner().y();

    olc::vf2d p = cf.tileCoordsToPixels(x, y, pge::RelativePosition::Center, 1.0f);

    // Compute the dimensions.
    float sx = area.w() * cf.tileSize().x;
    float sy = area.h() * cf.tileSize().y;

    // Render.
    pge->FillRectDecal(p, olc::vf2d(sx, sy), color);
  }

  void
  renderCircle(olc::PixelGameEngine* pge,
               const pge::CoordinateFrame& cf,
               const utils::Boxf& area,
               const olc::Pixel& color) noexcept
  {
    // We draw the circle at the center of the area.
    float x = area.x();
    float y = area.y();

    olc::vf2d p = cf.tileCoordsToPixels(x, y, pge::RelativePosition::Center, 1.0f);

    // Compute the dimensions. Note that we can only
    // draw a circle when sometimes we might want to
    // draw an ellipse. We will for now render the
    // circle with the smallest dimension.
    float s = std::min(area.w() * cf.tileSize().x, area.h() * cf.tileSize().y);

    // Render: note that the radius is half of the size.
    pge->FillCircle(p, s / 2.0f, color);
  }

}

namespace mas {
  namespace environment {

    Renderer::Renderer(const MovingObject& obj, const RenderingMode& mode):
      Component(Type::Renderer),

      m_obj(obj),

      m_mode(mode),
      m_color()
    {
      setService("mas");

      // Generate a random color.
      utils::RNG rng = utils::RNG::createRandomRNG();
      m_color.r = rng.rndInt(0, 255);
      m_color.g = rng.rndInt(0, 255);
      m_color.b = rng.rndInt(0, 255);
    }

    void
    Renderer::simulate(const time::Manager& /*manager*/) {}

    void
    Renderer::draw(olc::PixelGameEngine* pge,
                   const pge::CoordinateFrame& cf) const noexcept
    {
      // Differentiate based on the rendering mode.
      switch (m_mode) {
        case RenderingMode::Square:
          renderSquare(pge, cf, m_obj.bbox(), m_color);
          break;
        case RenderingMode::Circle:
          renderCircle(pge, cf, m_obj.bbox(), m_color);
          break;
        default:
          // Unhandled, do not render anything.
          break;
      }
    }

  }
}
