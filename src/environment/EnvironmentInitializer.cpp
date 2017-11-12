
#include "EnvironmentInitializer.h"
#include <chrono>

namespace environment
{
    const double EnvironmentInitializer::sk_defaultObjectsDimension(1.0);

    EnvironmentInitializer::EnvironmentInitializer(const unsigned int& objectsCount, const unsigned int& agentsCount, const utils::sdl::Area& spawnArea):
        m_objectsCount(objectsCount),
        m_agentsCount(agentsCount),
        m_spawnArea(spawnArea),
        m_density(2.0, 80.0),
        m_elasticity(0.65, 0.66)
    {
        // Nothing to d.
    }

    EnvironmentInitializer::~EnvironmentInitializer()
    {
        // Nothing to do.
    }

    void EnvironmentInitializer::operator()(Environment& environment)
    {
        // Create as many objects as needed.
        createObjects(environment);
        createAgents(environment);
    }

    void EnvironmentInitializer::createObjects(Environment& environment)
    {
        /*for (unsigned int indexObject = 0 ; indexObject < m_objectsCount ; ++indexObject)
        {
            const utils::Vector2d position(m_spawnArea());
            environment.spawnObject(std::make_shared<objects::EnvironmentalObject>(position.x(),
                                                                                   position.y(),
                                                                                   sk_defaultObjectsDimension,
                                                                                   sk_defaultObjectsDimension,
                                                                                   m_density(),
                                                                                   m_elasticity()));
        }*/
        const utils::Vector2d position(0.0, 0.0);
        environment.spawnObject(std::make_shared<objects::EnvironmentalObject>(position.x(),
                                                                               position.y(),
                                                                               10.0,
                                                                               sk_defaultObjectsDimension,
                                                                               2.0,
                                                                               0.95));
    }

    void EnvironmentInitializer::createAgents(Environment& environment)
    {
        /*for (unsigned int indexObject = 0 ; indexObject < m_agentsCount ; ++indexObject)
        {
            const utils::Vector2d position(m_spawnArea());
            environment.spawnAnimat(std::make_shared<agents::Animat>(position.x(),
                                                                     position.y(),
                                                                     m_density(),
                                                                     m_elasticity()));
        }*/

        /*const utils::Vector2d position(5.0, 0.0);
        environment.spawnAnimat(std::make_shared<agents::Animat>(position.x(),
                                                                 position.y(),
                                                                 50.0,
                                                                 0.65));*/

        const utils::Vector2d position2(3.5, -5.0);
        environment.spawnAnimat(std::make_shared<agents::Animat>(position2.x(),
                                                                 position2.y(),
                                                                 2.0,
                                                                 1.5));
    }
}
