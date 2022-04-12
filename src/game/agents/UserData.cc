
# include "UserData.hh"

namespace mas {
  namespace environment {

    UserData::UserData() noexcept:
      Component(Type::UserData)
    {}

    UserData::~UserData() noexcept {}

    void
    UserData::simulate(const time::Manager& /*manager*/) {}

  }
}
