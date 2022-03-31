
# include "Frustum.hh"

namespace mas {
  namespace environment {

    Frustum::Frustum(const utils::Boxf& area) noexcept:
      m_area(area)
    {}

    bool
    Frustum::visible(const MovingObject& obj) const noexcept {
      return m_area.intersects(obj.bbox());
    }

  }
}
