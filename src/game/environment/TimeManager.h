#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <vector>

namespace environment
{
    namespace time
    {
        enum class Unit
        {
            Nanosecond,
            Millisecond,
            Second,
            Minute,
            Hour,
            Day
        };

        class TimeManager {

            public:

                TimeManager(const double& initialTime = 0.0, const Unit& unit = Unit::Second);

                ~TimeManager();

                void increment(const double& time, const Unit& unit = Unit::Second);

                void decrement(const double& time, const Unit& unit = Unit::Second);

                double getLastStepDuration(const Unit& unit = Unit::Second) const;

                double getDurationSinceLaunch(const Unit& unit = Unit::Second) const;

            private:

                void handleTimeModification(const Unit& unit, const double& duration);

                static double convertDuration(const double& duration, const Unit& initialUnit, const Unit& targetUnit);

            private:

                static const double sk_defaultDurationsBufferLength;

                Unit m_unit;
                double m_time;

                std::vector<std::pair<Unit, double>> m_lastDurations;
        };
    }
}

#endif // TIMEMANAGER_H
