
#include <chrono>
#include "RandomNumberGenerator.h"

namespace utils
{
    namespace random
    {
        template <typename NumberType>
        RandomNumberGenerator<NumberType>::RandomNumberGenerator(const NumberType& minNumber, const NumberType& maxNumber):
            m_rng(),
            m_random()
        {
            // Setup the random number generator.
            uint64_t timeSeed(std::chrono::high_resolution_clock::now().time_since_epoch().count() + rand());
            std::seed_seq seed{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32)};
            setup(seed, minNumber, maxNumber);
        }

        template <typename NumberType>
        RandomNumberGenerator<NumberType>::~RandomNumberGenerator()
        {
            // Nothing to do.
        }

        template <typename NumberType>
        NumberType RandomNumberGenerator<NumberType>::operator()()
        {
            return m_random(m_rng);
        }

        template <typename NumberType>
        void RandomNumberGenerator<NumberType>::setup(std::seed_seq& seed, const NumberType& minNumber, const NumberType& maxNumber)
        {
            m_rng.seed(seed);
            m_random = std::uniform_real_distribution<double>(minNumber, maxNumber);
        }
    }
}
