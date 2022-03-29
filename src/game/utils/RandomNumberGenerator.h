#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>

namespace utils
{
    namespace random
    {
        template <typename NumberType>
        class RandomNumberGenerator
        {
            public:

                RandomNumberGenerator(const NumberType& minNumber, const NumberType& maxNumber);

                virtual ~RandomNumberGenerator();

                NumberType operator()();

            private:

                void setup(std::seed_seq& seed, const NumberType& minNumber, const NumberType& maxNumber);

            private:

                std::mt19937_64 m_rng;
                std::uniform_real_distribution<NumberType> m_random;

        };
    }
}

// Include implementation file.
#include "RandomNumberGenerator.hxx"

#endif // RANDOMNUMBERGENERATOR_H
