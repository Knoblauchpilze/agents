#ifndef    COORDINATE_FRAME_HXX
# define   COORDINATE_FRAME_HXX

# include "CoordinateFrame.hh"
# include <cmath>

namespace pge {

  inline
  const olc::vf2d&
  CoordinateFrame::tileScale() const noexcept {
    return m_scale;
  }

  inline
  olc::vf2d
  CoordinateFrame::tileSize() const noexcept {
    return m_scale * m_ts;
  }

  inline
  void
  CoordinateFrame::zoomIn(const olc::vf2d& pos) {
    zoom(0.5f, pos);
  }

  inline
  void
  CoordinateFrame::zoomOut(const olc::vf2d& pos) {
    zoom(2.0f, pos);
  }

  inline
  void
  CoordinateFrame::beginTranslation(const olc::vi2d& origin) {
    m_translationOrigin = origin;
    m_cachedPOrigin = m_pViewport.topLeft();
  }

  inline
  void
  CoordinateFrame::translate(const olc::vi2d& pos) {
    // We need to deduce the translation added by
    // the input `pos` assuming that this will be
    // the final position of the viewport.
    olc::vf2d translation = pos - m_translationOrigin;
    m_pViewport.topLeft() = m_cachedPOrigin + translation;
  }

  inline
  void
  CoordinateFrame::zoom(float factor, const olc::vf2d& pos) {
    // What we know is that the top left cell of
    // the viewport is at the top left corner of
    // the pixels viewport.
    // We can compute the distance from the `pos`
    // to the pixels viewport origin: it should
    // be applied the *inverse* of the `factor`
    // and we should be good to go: indeed if a
    // viewport has its span reduced, distances
    // are lengthened (and conversely).
    olc::vf2d d = m_pViewport.topLeft() - pos;
    d /= factor;

    m_pViewport.topLeft() = pos + d;

    // Also update the dimensions of the cells
    // viewport by `factor`.
    m_cViewport.dims() *= factor;

    updateTileScale();
  }

}

#endif    /* COORDINATE_FRAME_HXX */
