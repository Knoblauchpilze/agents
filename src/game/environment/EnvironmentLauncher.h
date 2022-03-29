#ifndef LAUNCHABLEENVIRONMENT_H
#define LAUNCHABLEENVIRONMENT_H

#include "Environment.h"
#include "TimeManager.h"
#include <thread>
#include <mutex>
#include <vector>
#include "SdlEventListener.h"

namespace environment
{
    namespace launcher
    {
        class EnvironmentLauncher: public application::sdl::EventListener
        {
            public:

                EnvironmentLauncher(const double& simulationFps, const double& simulationStep, const environment::time::Unit& unit);

                ~EnvironmentLauncher();

                void addRunnable(Environment* environment);

                void start();

                void pause();

                void resume();

                void stop();

                virtual void onExitEvent(const SDL_Event& exitEvent);

                virtual void onKeyReleasedEvent(const SDL_KeyboardEvent& keyEvent);

            private:

                void asynchronousRunningLoop();

                void runSimulationStep();

            private:

                enum class State
                {
                    None,
                    RunRequested,
                    Running,
                    PauseRequested,
                    Paused,
                    ResumeRequested,
                    StopRequested,
                    Stopped
                };

                static const double sk_minimumComputingTimeRemainingToSleep;

                std::vector<Environment*> m_environments;
                unsigned int m_simulationFps;
                std::mutex m_timeLocker;
                double m_simulationStep;
                environment::time::Unit m_unit;
                environment::time::TimeManager m_time;
                std::mutex m_locker;
                State m_state;
                std::shared_ptr<std::thread> m_simulationThread;


        };
    }
}

#endif // LAUNCHABLEENVIRONMENT_H
