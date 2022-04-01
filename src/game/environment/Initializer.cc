
# include "Initializer.hh"

namespace mas {
 namespace environment {

    Initializer::Initializer(const utils::Boxf& area):
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
