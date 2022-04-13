
# include "Behavior.hh"

namespace mas {
  namespace environment {

    Behavior::Behavior():
      utils::CoreObject("behavior")
    {
      setService("mas");
    }

    Behavior::~Behavior() {}

    void
    Behavior::attach(const utils::Uuid& uuid) noexcept {
      // Define a new name for the behavior so that it matches
      // the input identifier.
      setName(uuid.toString());
    }

  }
}
