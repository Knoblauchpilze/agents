
# include "TexturePack.hh"

namespace pge {

  TexturePack::TexturePack():
    utils::CoreObject("pack"),

    m_packs()
  {
    setService("textures");
  }

  TexturePack::~TexturePack() {
    for (unsigned id = 0 ; id < m_packs.size() ; ++id) {
      if (m_packs[id].res != nullptr) {
        delete m_packs[id].res;
      }
    }

    m_packs.clear();
  }

  unsigned
  TexturePack::registerPack(const sprites::Pack& pack) {
    // Load the file as a sprite and then convert it
    // to a faster `Decal` resource.
    olc::Sprite* spr = new olc::Sprite(pack.file);
    if (spr == nullptr) {
      error(
        "Failed to load texture pack \"" + pack.file + "\"",
        "Loading returned null"
      );
    }

    // Build the internal structure, register it and
    // return the corresponding identifier.
    Pack p;
    p.sSize = pack.sSize;
    p.layout = pack.layout;

    p.res = new olc::Decal(spr);

    unsigned id = m_packs.size();
    m_packs.push_back(p);

    return id;
  }

  void
  TexturePack::draw(olc::PixelGameEngine* pge,
                    const sprites::Sprite& s,
                    const olc::vf2d& p,
                    const olc::vf2d& scale) const
  {
    // Check whether the pack is valid.
    if (s.pack >= m_packs.size()) {
      warn("Unable to draw sprite from pack " + std::to_string(s.pack));
      return;
    }

    const Pack& tp = m_packs[s.pack];

    olc::vi2d sCoords = spriteCoords(tp, s.sprite, s.id);
    pge->DrawPartialDecal(p, tp.res, sCoords, tp.sSize, scale, s.tint);
  }

}
