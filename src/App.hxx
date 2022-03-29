#ifndef    APP_HXX
# define   APP_HXX

# include "App.hh"
# include "Action.hh"

namespace pge {

  inline
  void
  App::drawSprite(const SpriteDesc& t, const CoordinateFrame& cf) {
    olc::vf2d p = cf.tileCoordsToPixels(t.x, t.y, t.loc, t.radius);

    m_packs->draw(this, t.sprite, p, t.radius * cf.tileScale());
  }

  inline
  void
  App::drawRect(const SpriteDesc& t,
                const CoordinateFrame& cf)
  {
    olc::vf2d p = cf.tileCoordsToPixels(t.x, t.y, t.loc, t.radius);
    FillRectDecal(p, t.radius * cf.tileSize(), t.sprite.tint);
  }

}

#endif    /* APP_HXX */
