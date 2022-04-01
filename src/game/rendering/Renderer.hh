#ifndef    RENDERER_HH
# define   RENDERER_HH

# include <memory>
# include "Component.hh"
# include "MovingObject.hh"

namespace mas {
  namespace environment {

    class Renderer: public Component {
      public:

        /**
         * @brief - Create a new renderer with the specified moving
         *          object.
         */
        Renderer(const MovingObject& obj);

      private:

        /**
         * @brief - The moving object attached to this renderer.
         */
        const MovingObject& m_obj;
    };

  }
}

#endif    /* RENDERER_HH */
