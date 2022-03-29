
#include "EnvironmentLauncher.h"
#include "InternalException.h"
#include <SDL/SDL.h>

namespace environment
{
    namespace launcher
    {
        const double EnvironmentLauncher::sk_minimumComputingTimeRemainingToSleep(3.0);

        EnvironmentLauncher::EnvironmentLauncher(const double& simulationFps, const double& simulationStep, const environment::time::Unit& unit):
            application::sdl::EventListener(),
            m_environments(),
            m_simulationFps(simulationFps),
            m_timeLocker(),
            m_simulationStep(simulationStep),
            m_unit(unit),
            m_time(0.0, unit),
            m_locker(),
            m_state(State::None),
            m_simulationThread(nullptr)
        {
            // Nothing to do.
        }

        EnvironmentLauncher::~EnvironmentLauncher()
        {
            stop();
        }

        void EnvironmentLauncher::addRunnable(Environment* environment)
        {
            m_environments.push_back(environment);
        }

        void EnvironmentLauncher::start()
        {
            m_locker.lock();
            if (m_state == State::None || m_state == State::Stopped)
            {
                m_state = State::RunRequested;
                m_locker.unlock();
                m_simulationThread = std::make_shared<std::thread>(&EnvironmentLauncher::asynchronousRunningLoop, this);
            }
            else
            {
                m_locker.unlock();
            }
        }

        void EnvironmentLauncher::pause()
        {
            m_locker.lock();
            if (m_state == State::Running)
            {
                m_state = State::PauseRequested;
            }
            m_locker.unlock();
        }

        void EnvironmentLauncher::resume()
        {
            m_locker.lock();
            if (m_state == State::Paused)
            {
                m_state = State::ResumeRequested;
            }
            m_locker.unlock();
        }

        void EnvironmentLauncher::stop()
        {
            std::lock_guard<std::mutex>lock(m_locker);
            if (m_simulationThread == nullptr) {
                if (m_state != State::None && m_state != State::Stopped) {
                    // Bad state
                    m_simulationThread.reset();
                    throw core::exceptions::InternalException(std::string("Error: Cannot stop the simulation, not started"));
                }
            }
            else {
                m_state = State::StopRequested;
                m_locker.unlock();
                // Wait
                m_simulationThread->join();
                // Destroy the thread
                m_simulationThread.reset();
                // Check the execution status
                if (m_state != State::Stopped) {
                    throw core::exceptions::InternalException(std::string("Error: Execution thread handled in error"));
                }
            }
        }

        void EnvironmentLauncher::onExitEvent(const SDL_Event&)
        {
            stop();
        }

        void EnvironmentLauncher::onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent)
        {
            if (keyEvent.keysym.sym == SDLK_p)
            {
                pause();
            }
            else if (keyEvent.keysym.sym == SDLK_r)
            {
                resume();
            }
            else
            {
                // Do nothing.
            }
        }

        void EnvironmentLauncher::asynchronousRunningLoop()
        {
            // The simulation is now running
            m_locker.lock();
            m_state = State::Running;
            m_locker.unlock();
            // Run simulation steps
            bool done(false);
            do
            {
                // Handle stop, pause and resume request
                m_locker.lock();
                if (m_state == State::PauseRequested)
                {

                    std::cout << "[LAUNCHER] Pausing environment simulation..." << std::endl;

                    m_state = State::Paused;
                    m_locker.unlock();
                }
                else if (m_state == State::ResumeRequested)
                {

                    std::cout << "[LAUNCHER] Resuming environment simulation..." << std::endl;

                    m_state = State::Running;
                    m_locker.unlock();
                }
                else if (m_state == State::StopRequested)
                {

                    std::cout << "[LAUNCHER] Stopping environment simulation..." << std::endl;

                    m_state = State::Stopped;
                    m_locker.unlock();
                    done = true;
                }
                else if (m_state == State::Running)
                {
                    m_locker.unlock();
                    runSimulationStep();
                }
                else
                {
                    // Not handled or nothing to do (e.g. Paused).
                    m_locker.unlock();
                }
            }
            while (!done);
        }

        void EnvironmentLauncher::runSimulationStep()
        {
            // Retrieve the parameters of the current step
            std::lock_guard<std::mutex> lock(m_timeLocker);
            const double currentSimulationStepComputingDuration(1000.0 / m_simulationFps);
            // Update the time manager.
            m_time.increment(m_simulationStep, m_unit);
            // Start a timer to track the duration of the simulation.
            const unsigned int startingSimulationTime(SDL_GetTicks());
            // Simulate the current step on each runnable.
            for (std::vector<Environment*>::iterator environment = m_environments.begin() ;
                 environment != m_environments.end() ;
                 ++environment)
            {
                (*environment)->simulate(m_time);
            }
            // Compute the duration of the simulation
            const double simulationDuration(static_cast<double>(SDL_GetTicks() - startingSimulationTime));
            // Compare with the desired frame rate and delay if needed
            if (simulationDuration > currentSimulationStepComputingDuration) {
                std::cerr << "[LAUNCHER] Frame took " << simulationDuration << "ms which is greater than the " << currentSimulationStepComputingDuration << "ms authorized to maintain " << m_simulationFps << "fps" << std::endl;
            }
            else {
                // Compute if we actually need to sleep: if there's only 1ms remaining, we might as well start the next simulation asap.
                const double remainingDuration(currentSimulationStepComputingDuration - simulationDuration);
                if (remainingDuration > sk_minimumComputingTimeRemainingToSleep) {
                    SDL_Delay(static_cast<Uint32>(remainingDuration));
                }
            }
        }
    }
}
