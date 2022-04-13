#ifndef    AGENTS_HH
# define   AGENTS_HH

# include "Agent.hh"
# include "Animat.hh"

namespace mas {
  namespace environment {

    /**
     * @brief - Generate a new agent representing a fish (which is
     *          a social creature trying to move towards the center
     *          of all the perceived other fishes) and attach it to
     *          the input animat.
     * @param animat - the animat to attach to the agent.
     * @return - the agent.
     */
    AgentShPtr
    createFish(Animat& animat);

  }
}

#endif    /* AGENTS_HH */
