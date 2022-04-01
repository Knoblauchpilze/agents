
# include "Renderer.hh"

namespace mas {
  namespace environment {

    Renderer::Renderer(const MovingObject& obj):
      Component(Type::Renderer),

      m_obj(obj)
    {
      setService("mas");
    }

  }
}
