#ifndef ENVIRONMENTINITIALIZER_H
#define ENVIRONMENTINITIALIZER_H

#include "Area.h"
#include "Environment.h"
#include "RandomNumberGenerator.h"
#include "RandomPositionGenerator.h"

namespace environment
{
    class Environment;

    class EnvironmentInitializer
    {
        public:

            EnvironmentInitializer(const unsigned int& objectsCount, const unsigned int& agentsCount, const utils::sdl::Area& spawnArea);

            ~EnvironmentInitializer();

            void operator()(Environment& environment);

        private:

            void createObjects(Environment& environment);

            void createAgents(Environment& environment);

        private:

            static const double sk_defaultObjectsDimension;

            unsigned int m_objectsCount;
            unsigned int m_agentsCount;
            utils::random::RandomPositionGenerator m_spawnArea;
            utils::random::RandomNumberGenerator<double> m_density;
            utils::random::RandomNumberGenerator<double> m_elasticity;
    };
}

#endif // ENVIRONMENTINITIALIZER_H
