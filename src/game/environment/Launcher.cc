
# include "Launcher.hh"
# include <core_utils/TimeUtils.hh>

/// @brief - The minimum duration for which we will sleep
/// in case the processing of a simulation step is short
/// enough to consider sleeping.
# define MINIMUM_SLEEP_TIME 3

namespace mas {

  std::string
  stateToString(const State& state) noexcept {
    switch (state) {
      case State::None:
        return "\"none\"";
      case State::RunRequested:
        return "\"run requested\"";
      case State::Running:
        return "\"running\"";
      case State::PauseRequested:
        return "\"pause requested\"";
      case State::Paused:
        return "\"paused\"";
      case State::ResumeRequested:
        return "\"resume requested\"";
      case State::StopRequested:
        return "\"stop requested\"";
      case State::Stopped:
        return "\"stopped\"";
      default:
        return "\"unknown\"";
    }
  }

  Launcher::Launcher(Environment* env,
                     float fps,
                     float step,
                     const time::Unit& unit):
    utils::CoreObject("launcher"),

    m_env(env),

    m_simThreadLocker(),
    m_simThread(nullptr),
    m_state(State::None),

    m_desiredFPS(fps),
    m_step(step),
    m_stepUnit(unit),

    m_time(0.0f, m_stepUnit)
  {
    setService("mas");
  }

  Launcher::~Launcher() {
    stop();
  }

  void
  Launcher::start() {
    Guard guard(m_simThreadLocker);
    if (m_state != State::None && m_state != State::Stopped) {
      return;
    }

    m_state = State::RunRequested;
    m_simThreadLocker.unlock();

    m_simThread = std::make_shared<std::thread>(&Launcher::asynchronousRunningLoop, this);
  }

  void
  Launcher::pause() {
    Guard guard(m_simThreadLocker);
    if (m_state == State::Running) {
      m_state = State::PauseRequested;
    }
  }

  void
  Launcher::resume() {
    Guard guard(m_simThreadLocker);
    if (m_state == State::Paused) {
      m_state = State::ResumeRequested;
    }
  }

  void
  Launcher::stop() {
    m_simThreadLocker.lock();

    if (m_simThread == nullptr) {
      m_simThreadLocker.unlock();

      // Bad state.
      if (m_state != State::None && m_state != State::Stopped) {
        m_simThread.reset();
        error(
          "Failed to stop the simulation",
          "Unexpected state " + stateToString(m_state)
        );
      }

      return;
    }

    m_state = State::StopRequested;
    m_simThreadLocker.unlock();

    // Wait for the thread to terminate.
    m_simThread->join();
    m_simThread.reset();

    if (m_state != State::Stopped) {
      error(
        "Failed to stop the simulation",
        "Reached unexpected state " + stateToString(m_state)
      );
    }
  }

  void
  Launcher::step() {
    Guard guard(m_simThreadLocker);

    // Can't step if the simulation is running.
    if (m_state != State::Paused && m_state != State::Stopped && m_state != State::None) {
      warn(
        "Failed to simulate a single step",
        "Unexpected simulation state " + stateToString(m_state)
      );
      return;
    }

    log("Performing single simulation step", utils::Level::Info);
    simulate(false);
  }

  void
  Launcher::asynchronousRunningLoop() {
    // The simulation is now running.
    {
      Guard guard(m_simThreadLocker);
      m_state = State::Running;
    }

    // Run simulation steps
    bool done = false;
    while (!done) {
      // Handle stop, pause and resume request
      m_simThreadLocker.lock();

      switch (m_state) {
        case State::PauseRequested:
          log("Pausing environment simulation", utils::Level::Info);
          m_state = State::Paused;
          m_simThreadLocker.unlock();
          break;
        case State::ResumeRequested:
          log("Resuming environment simulation", utils::Level::Info);
          m_state = State::Running;
          m_simThreadLocker.unlock();
          break;
        case State::StopRequested:
          log("Stopping environment simulation", utils::Level::Info);
          m_state = State::Stopped;
          m_simThreadLocker.unlock();
          done = true;
          break;
        case State::Running:
          m_simThreadLocker.unlock();
          simulate(true);
          break;
        default:
          // Not handled or nothing to do (e.g. Paused).
          m_simThreadLocker.unlock();
          break;
      }
    }
  }

  void
  Launcher::simulate(bool sleep) {
    // Update the time manager by one increment.
    m_time.increment(m_step, m_stepUnit);

    // Simulate the current step.
    utils::TimeStamp s = utils::now();
    m_env->simulate(m_time);
    utils::Duration d = utils::now() - s;

    utils::Duration expected = utils::toMilliseconds(1000.0f / m_desiredFPS);
    if (d > expected) {
      warn("Took " + utils::durationToString(d) + "ms to compute frame, expected " + utils::durationToString(expected) + "ms");
      return;
    }

    // Wait for a bit if needed.
    utils::Duration remaining = expected - d;
    if (sleep && remaining > utils::toMilliseconds(MINIMUM_SLEEP_TIME)) {
      std::this_thread::sleep_for(remaining);
    }
  }

}
