#ifndef    LAUNCHER_HH
# define   LAUNCHER_HH

# include <mutex>
# include <thread>
# include <core_utils/CoreObject.hh>
# include "Environment.hh"
# include "Manager.hh"

namespace mas {

  /// @brief - Enumeration defining the state of the simulation.
  enum class State {
    None,
    RunRequested,
    Running,
    PauseRequested,
    Paused,
    ResumeRequested,
    StopRequested,
    Stopped
  };

  /**
   * @brief - Convert a state to a human readable string.
   * @param state - the state to convert.
   * @return - the corresponding string.
   */
  std::string
  stateToString(const State& state) noexcept;

  class Launcher: public utils::CoreObject {
    public:

      /**
       * @brief - Create a new launcher with the desired properties.
       * @param env - the environment to simulate.
       * @param fps - the desired framerate for the simulation.
       * @param step - the duration of each simulation step.
       * @param unit - the unit of the step (used to interpret the
       *               previous parameter).
       */
      Launcher(Environment* env,
               float fps,
               float step,
               const time::Unit& unit);

      /**
       * @brief - Release the resource used by this launcher and
       *          handles gracefully shutting down the simulation.
       */
      ~Launcher();

      /**
       * @brief - Start the simulation. Nothing happens in case
       *          it is already running.
       */
      void
      start();

      /**
       * @brief - Pause the simulation. Nothing happens in case
       *          the simulation is stopped or already paused.
       */
      void
      pause();

      /**
       * @brief - Resume the simulation. Nothing happens in case
       *          it is already running.
       */
      void
      resume();

      /**
       * @brief - Stop the simulation. Nothing happens in case
       *          it is not started.
       */
      void
      stop();

      /**
       * @brief - Perform a single simulation step. Nothing happens
       *          in case the simulation is running. Otherwise the
       *          state is restored to its previous state.
       */
      void
      step();

    private:

      /**
       * @brief - Asynchronous method launched in a thread which
       *          allows to simulate the environment attached to
       *          the launcher at regular intervals.
       */
      void
      asynchronousRunningLoop();

      /**
       * @brief - Used to run a single simulation step. The input
       *          boolean indicates whether the method should make
       *          the current thread sleep in order to maintain
       *          the desired FPS or not.
       * @param sleep - `true` if the FPS should be considered or
       *                not.
       */
      void
      simulate(bool sleep);

    private:

      /// @brief - Convenience define for a lock guard.
      using Guard = std::lock_guard<std::mutex>;

      /**
       * @brief - The environment attached to this launcher.
       */
      Environment* m_env;

      /**
       * @brief - A mutex to protect the access to the simulation
       *          thread.
       */
      std::mutex m_simThreadLocker;

      /**
       * @brief - The thread used to handle the simulation. This
       *          is initialized only when the simulation starts.
       */
      std::shared_ptr<std::thread> m_simThread;

      /**
       * @brief - The state of the simulation. Updated with the
       *          latest status of the execution.
       */
      State m_state;

      /**
       * @brief - The desired framerate for the simulation.
       */
      float m_desiredFPS;

      /**
       * @brief - The duration of a single simulation step.
       */
      float m_step;

      /**
       * @brief - The unit of the simulation step.
       */
      time::Unit m_stepUnit;

      /**
       * @brief - The object allowing to manage the time passing
       *          in the simulation.
       */
      time::Manager m_time;
  };

}

#endif    /* LAUNCHER_HH */
