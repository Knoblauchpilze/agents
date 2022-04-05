#ifndef    INITIALIZATION_HH
# define   INITIALIZATION_HH

# include "Environment.hh"
# include "Launcher.hh"
# include "Initializer.hh"

namespace mas {
  namespace environment {

    /**
     * @brief - Create the launcher from the environment with
     *          a default framerate.
     * @param env - the environment to attach to the launcher.
     * @return - an environment initializer.
     */
    Launcher
    createLauncher(Environment& env) noexcept;

    /**
     * @brief - Initialize the input environment.
     * @param env - the environment to initialize.
     */
    void
    initialize(Environment& env) noexcept;

  }
}

#endif    /* INITIALIZATION_HH */
