
#include <chrono>
#include "RandomPositionGenerator.h"

namespace utils
{
    namespace random
    {
        RandomPositionGenerator::RandomPositionGenerator(const utils::sdl::Area& area):
            m_area(area),
            m_rng(),
            m_randomX(),
            m_randomY()
        {
            // Setup the random number generator.
            uint64_t timeSeed(std::chrono::high_resolution_clock::now().time_since_epoch().count() + rand());
            std::seed_seq seed{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32)};
            setup(seed);
        }

        RandomPositionGenerator::~RandomPositionGenerator()
        {
            // Nothing to do.
        }

        utils::Vector2d RandomPositionGenerator::operator()()
        {
            return utils::Vector2d(m_randomX(m_rng), m_randomY(m_rng));
        }

        void RandomPositionGenerator::setup(std::seed_seq& seed)
        {
            m_rng.seed(seed);
            m_randomX = std::uniform_real_distribution<double>(m_area.getLeftBound(), m_area.getRightBound());
            m_randomY = std::uniform_real_distribution<double>(m_area.getBottomBound(), m_area.getTopBound());
        }
    }
}
