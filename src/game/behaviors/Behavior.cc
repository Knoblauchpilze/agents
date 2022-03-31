
# include "Behavior.hh"

namespace mas {
  namespace environment {

    Behavior::Behavior():
      utils::CoreObject("behavior")
    {
      setService("mas");
    }

    Behavior::~Behavior() {}

    utils::Vector2f
    Behavior::nearest(const utils::Vector2f& p, const Perception& perception) const noexcept {
      utils::Vector2f out;

      const utils::Boxf& box(perception.bbox());
      if (p.x() <= box.getLeftBound()) {
        out.x() = box.getLeftBound();
      }
      else if (p.x() >= box.getRightBound()) {
        out.x() = box.getRightBound();
      }
      else {
        out.x() = p.x();
      }

      if (p.y() <= box.getBottomBound()) {
        out.y() = box.getBottomBound();
      }
      else if (p.y() >= box.getTopBound()) {
        out.y() = box.getTopBound();
      }
      else {
        out.y() = p.y();
      }

      return out;
    }

  }
}
