#ifndef RANDOMPOSITIONGENERATOR_H
#define RANDOMPOSITIONGENERATOR_H

#include <random>
#include "Area.h"
#include "Vector2d.h"

namespace utils
{
    namespace random
    {
        class RandomPositionGenerator
        {
            public:

                RandomPositionGenerator(const utils::sdl::Area& area);

                virtual ~RandomPositionGenerator();

                utils::Vector2d operator()();

            private:

                void setup(std::seed_seq& seed);

            private:

                utils::sdl::Area m_area;
                std::mt19937_64 m_rng;
                std::uniform_real_distribution<double> m_randomX;
                std::uniform_real_distribution<double> m_randomY;

        };
    }
}

#endif // RANDOMPOSITIONGENERATOR_H
