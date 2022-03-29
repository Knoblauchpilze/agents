
# include "Viewport.hh"

namespace pge {

  Viewport::Viewport(const olc::vf2d& tl,
                     const olc::vf2d& dims) noexcept:
    m_tl(tl),
    m_dims(dims),

    m_dirty(false),
    m_max(m_tl + dims)
  {}

  olc::vf2d&
  Viewport::topLeft() noexcept {
    m_dirty = true;
    return m_tl;
  }

  const olc::vf2d&
  Viewport::topLeft() const noexcept {
    return m_tl;
  }

  olc::vf2d&
  Viewport::dims() noexcept {
    m_dirty = true;
    return m_dims;
  }

  const olc::vf2d&
  Viewport::dims() const noexcept {
    return m_dims;
  }

  bool
  Viewport::visible(const utils::Point2i& p, float radius) const noexcept {
    // Update bounds for the viewport if needed.
    if (m_dirty) {
      m_max = m_tl + m_dims;
      m_dirty = false;
    }

    // If the element is fully out of the x span
    // or out of the y span, then it is not visible.
    if (p.x() + radius < m_tl.x || p.x() - radius > m_max.x) {
      return false;
    }

    if (p.y() + radius < m_tl.y || p.y() - radius > m_max.y) {
      return false;
    }

    return true;
  }

  bool
  Viewport::visible(const olc::vf2d& p, const olc::vf2d& sz) const noexcept {
    // Update bounds for the viewport if needed.
    if (m_dirty) {
      m_max = m_tl + m_dims;
      m_dirty = false;
    }

    // If the element is fully out of the x span
    // or out of the y span, then it is not visible.
    if (p.x + sz.x < m_tl.x || p.x - sz.x > m_max.x) {
      return false;
    }

    if (p.y + sz.y < m_tl.y || p.y - sz.y > m_max.y) {
      return false;
    }

    return true;
  }

}
