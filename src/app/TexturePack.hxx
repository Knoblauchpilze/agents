#ifndef    TEXTURE_PACK_HXX
# define   TEXTURE_PACK_HXX

# include "TexturePack.hh"
# include "utils.hh"

namespace pge {

  inline
  void
  TexturePack::draw(olc::PixelGameEngine* pge,
                    const sprites::Sprite& s,
                    const olc::vf2d& p,
                    float scale) const
  {
    draw(pge, s, p, olc::vf2d(scale, scale));
  }

  inline
  olc::vi2d
  TexturePack::spriteCoords(const Pack& pack,
                            const olc::vi2d& coord,
                            int id) const
  {
    int lID = coord.y * pack.layout.x + coord.x + id;

    // Go back to 2D coordinates using the layout on
    // the linearized ID and the size of the sprite
    // to obtain a pixels position.
    return olc::vi2d(
      (lID % pack.layout.x) * pack.sSize.x,
      (lID / pack.layout.x) * pack.sSize.y
    );
  }

}

#endif    /* TEXTURE_PACK_HXX */
