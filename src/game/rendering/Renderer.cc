
# include "Renderer.hh"
# include <core_utils/RNG.hh>

namespace mas {
  namespace environment {

    Renderer::Renderer(const MovingObject& obj):
      Component(Type::Renderer),

      m_obj(obj),

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
    Renderer::draw(olc::PixelGameEngine* pge,
                   const pge::CoordinateFrame& cf) const noexcept
    {
      const utils::Boxf& area = m_obj.bbox();

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
      pge->FillRectDecal(p, olc::vf2d(sx, sy), m_color);
    }

  }
}
