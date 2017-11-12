
#include "TimeManager.h"

namespace environment
{
    namespace time
    {

        const double TimeManager::sk_defaultDurationsBufferLength(10);

        TimeManager::TimeManager(const double& initialTime, const Unit& unit) :
            m_unit(unit),
            m_time(initialTime),
            m_lastDurations()
        {
            // Nothing to do
        }

        TimeManager::~TimeManager() {
            // Nothing to do
        }

        void TimeManager::increment(const double& time, const Unit& unit) {
            handleTimeModification(unit, time);
        }

        void TimeManager::decrement(const double& time, const Unit& unit) {
            handleTimeModification(unit, -time);
        }

        double TimeManager::getLastStepDuration(const Unit& unit) const {
            double lastDuration(0.0);
            if (m_lastDurations.size() > 0) {
                std::pair<Unit, double> lastStep = m_lastDurations.front();
                lastDuration = convertDuration(lastStep.second, lastStep.first, unit);
            }
            return lastDuration;
        }

        double TimeManager::getDurationSinceLaunch(const Unit& unit) const {
            return convertDuration(m_time, m_unit, unit);
        }

        void TimeManager::handleTimeModification(const Unit& unit, const double& duration) {
            double standardizedDuration = convertDuration(duration, unit, m_unit);
            m_time += standardizedDuration;
            // Add the step to the buffer
            m_lastDurations.insert(m_lastDurations.begin(), std::make_pair(unit, duration));
            if (m_lastDurations.size() > sk_defaultDurationsBufferLength) {
                m_lastDurations.pop_back();
            }
        }

        double TimeManager::convertDuration(const double& duration, const Unit& initialUnit, const Unit& targetUnit) {
            // Convert the source into seconds
            double sourceToSeconds(1.0);
            switch (initialUnit) {
            case Unit::Millisecond:
                sourceToSeconds = 0.001;
                break;
            case Unit::Second:
                sourceToSeconds = 1.0;
                break;
            case Unit::Minute:
                sourceToSeconds = 60.0;
                break;
            case Unit::Hour:
                sourceToSeconds = 60.0 * 60.0;
                break;
            case Unit::Day:
                sourceToSeconds = 60.0 * 60.0 * 24.0;
                break;
            default:
                // Assume it is second
                break;
            }
            double secondsDuration = duration * sourceToSeconds;
            // Convert back into desired unit
            double secondsToTarget(1.0);
            switch (targetUnit) {
            case Unit::Millisecond:
                secondsToTarget = 1.0 / 0.001;
                break;
            case Unit::Second:
                secondsToTarget = 1.0 / 1.0;
                break;
            case Unit::Minute:
                secondsToTarget = 1.0 / 60.0;
                break;
            case Unit::Hour:
                secondsToTarget = 1.0 / (60.0 * 60.0);
                break;
            case Unit::Day:
                secondsToTarget = 1.0 / (60.0 * 60.0 * 24.0);
                break;
            default:
                // Assume it is second
                break;
            }
            return secondsDuration * secondsToTarget;
        }
    }
}
