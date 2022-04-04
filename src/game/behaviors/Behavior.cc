
# include "Behavior.hh"

namespace mas {
  namespace environment {

    Behavior::Behavior():
      utils::CoreObject("behavior")
    {
      setService("mas");
    }

    Behavior::~Behavior() {}

  }
}
