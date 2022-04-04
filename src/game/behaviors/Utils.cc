
# include "Utils.hh"

namespace mas {
  namespace environment {

    utils::Point2f
    nearestPoint(const utils::Point2f& p, const utils::Boxf& area) noexcept {
      utils::Vector2f out;

      if (p.x() <= area.getLeftBound()) {
        out.x() = area.getLeftBound();
      }
      else if (p.x() >= area.getRightBound()) {
        out.x() = area.getRightBound();
      }
      else {
        out.x() = p.x();
      }

      if (p.y() <= area.getBottomBound()) {
        out.y() = area.getBottomBound();
      }
      else if (p.y() >= area.getTopBound()) {
        out.y() = area.getTopBound();
      }
      else {
        out.y() = p.y();
      }

      return out;
    }

  }
}
