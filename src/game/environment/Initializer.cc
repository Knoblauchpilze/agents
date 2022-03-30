
# include "Initializer.hh"

namespace mas {
 namespace environment {

    Initializer::Initializer(const utils::Vector2f& area):
      utils::CoreObject("initializer"),

      m_area(area)
    {
      setService("mas");
    }

    void
    Initializer::operator()(Environment& /*env*/) {
      /// TODO: Handle this.
    }

 }
}
