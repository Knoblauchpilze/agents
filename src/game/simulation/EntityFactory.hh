#ifndef    ENTITY_FACTORY_HH
# define   ENTITY_FACTORY_HH

# include "Initializer.hh"

namespace mas {
  namespace environment {

    /**
     * @brief - Generate a factory to generate entities.
     * @return - the entity factory.
     */
    EntityFactory
    createFactory();

  }
}

#endif    /* ENTITY_FACTORY_HH */
