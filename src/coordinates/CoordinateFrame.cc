
# include "CoordinateFrame.hh"
# include "utils.hh"

namespace pge {

  CoordinateFrame::CoordinateFrame(const Viewport& cvp,
                                   const Viewport& pvp,
                                   const olc::vi2d& tileSize):
    utils::CoreObject("frame"),

    m_cViewport(cvp),
    m_pViewport(pvp),

    m_ts(tileSize),
    m_scale(1.0f, 1.0f),
    m_tScaled(m_ts),

    m_translationOrigin(),
    m_cachedPOrigin()
  {
    setService("coordinate");

    // Update the tiles scale based on the viewport.
    updateTileScale();
  }

  void
  CoordinateFrame::updateTileScale() {
    m_tScaled = m_pViewport.dims() / m_cViewport.dims();
    m_scale = m_tScaled / m_ts;

    verbose(
      "Tile size is " + toString(m_ts) + ", scale is " + toString(m_scale)
    );
  }

}
