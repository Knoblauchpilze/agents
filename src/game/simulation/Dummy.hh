#ifndef    DUMMY_HH
# define   DUMMY_HH

# include "Agent.hh"
# include "Animat.hh"

namespace mas {
  namespace environment {

    /**
     * @brief - Generate a dummy agent and attached it to the
     *          animat.
     * @param animat - the animat to attach to the agent.
     * @return - the agent.
     */
    AgentShPtr
    createDummy(Animat& animat);

  }
}

#endif    /* DUMMY_HH */
