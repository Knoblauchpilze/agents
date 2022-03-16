
#include <iostream>
#include "Environment.h"
#include "BodyDrawer.h"

namespace environment
{
    Environment::Environment():
        m_objects(),
        m_bodies(),
        m_agents(),
        m_animats(),
        m_physicEngine(),
        m_drawables(),
        m_updater(),
        m_listeners()
    {
        // Nothing to do.
    }

    Environment::~Environment()
    {
        // Nothing to do.
    }

    void Environment::create(EnvironmentInitializer& initializer)
    {
        initializer(*this);
    }

    void Environment::addListener(listener::EnvironmentListener* listener)
    {
        m_listeners.push_back(listener);
    }


    void Environment::simulate(const time::TimeManager& manager)
    {
        //std::cout << "[ENVIRONMENT] Simulating " << m_objects.size() << " objects for " << manager.getElapsedTime(time::Unit::Second) << "s" << std::endl;
        computePreAgentsStep(manager);
        computeAgentsStep(manager);
        computePostAgentsStep(manager);
        fireEnvironmentChange();
    }

    void Environment::spawnObject(const objects::EnvironmentalObjectShPtr object)
    {
        if (object)
        {
            m_objects.insert(std::make_pair(core::uuid::Uuid(), object));
            objects::drawable::EnvironmentalObjectDrawerShPtr drawer(std::make_shared<objects::drawable::EnvironmentalObjectDrawer>(*object));
            object->addListener(drawer.get());
            // Force using the constant method.
            const objects::EnvironmentalObject* rawObject(object.get());
            m_physicEngine.registerBody(rawObject->getRigidBody());
            m_drawables.push_back(drawer);
            m_updater.registerObjectDrawable(drawer);
        }
    }

    void Environment::spawnAnimat(agents::AnimatShPtr animat)
    {
        if (animat)
        {
            // Retrieve the agent and body.
            agents::AgentShPtr agent(animat->spawnAgent());
            objects::BodyShPtr body(animat->spawnBody());
            // Add these objects to the correct table.
            m_bodies.insert(std::make_pair(core::uuid::Uuid(), body));
            m_agents.insert(std::make_pair(core::uuid::Uuid(), agent));
            m_animats.push_back(animat);
            // Create body drawable.
            objects::drawable::BodyDrawerShPtr drawer(std::make_shared<objects::drawable::BodyDrawer>(*body));
            body->addListener(drawer.get());
            // Force using the constant method.
            const objects::EnvironmentalObject* rawBody(body.get());
            m_physicEngine.registerBody(rawBody->getRigidBody());
            m_drawables.push_back(drawer);
            m_updater.registerObjectDrawable(drawer);
            m_updater.registerBodyDrawable(drawer);
        }
	}

    const std::vector<objects::drawable::EnvironmentalObjectDrawerShPtr>& Environment::getDrawables() const
    {
        return m_drawables;
    }

    environment::drawable::DrawableUpdater& Environment::getDrawablesUpdater()
    {
        return m_updater;
    }

    //===============

    void Environment::computePerceptions()
    {
		for (std::unordered_map<core::uuid::Uuid, environment::objects::BodyShPtr>::const_iterator bodiesIterator = m_bodies.cbegin();
			bodiesIterator != m_bodies.cend();
			++bodiesIterator)
        {
            if (bodiesIterator->second != nullptr)
            {
                computePerceptionsForBody(*bodiesIterator->second);
            }
        }
    }

    void Environment::applyInfluences(std::vector<environment::agents::influences::InfluenceShPtr>& influences)
    {
        // Apply each influence, without handling conflicts for now
        for (std::vector<environment::agents::influences::InfluenceShPtr>::iterator influencesIterator = influences.begin();
            influencesIterator != influences.end();
            ++influencesIterator)
        {
            (*influencesIterator)->apply();
        }
    }

    //===============

    void Environment::fireEnvironmentChange()
    {
        for (std::vector<listener::EnvironmentListener*>::iterator listener = m_listeners.begin() ; listener != m_listeners.end() ; ++listener)
        {
            (*listener)->onEnvironmentUpdate();
        }
    }

    void Environment::computePreAgentsStep(const time::TimeManager& /*manager*/)
    {
        computePerceptions();
    }

    void Environment::computeAgentsStep(const time::TimeManager& /*manager*/)
    {
		for (std::unordered_map<core::uuid::Uuid, environment::agents::AgentShPtr>::const_iterator agentsIterator = m_agents.cbegin();
			agentsIterator != m_agents.cend();
			++agentsIterator) {
			agentsIterator->second->live();
		}
    }

    void Environment::computePostAgentsStep(const time::TimeManager& manager)
    {
		std::vector<environment::agents::influences::InfluenceShPtr> influences;
		collectInfluences(influences);
		m_physicEngine.simulate(manager);
		applyInfluences(influences);
		applyEndogenous(manager);
    }

    void Environment::collectInfluences(std::vector<environment::agents::influences::InfluenceShPtr>& influences)
    {
		influences.clear();
		// Search for intersections with other bodies
		for (std::unordered_map<core::uuid::Uuid, environment::objects::BodyShPtr>::const_iterator bodiesIterator = m_bodies.cbegin();
			bodiesIterator != m_bodies.cend();
			++bodiesIterator)
        {
			// Consume the influences of the body
			const std::vector<environment::agents::influences::InfluenceShPtr> bodyInfluences(bodiesIterator->second->consumeInfluences());
			// Insert each one in the internal list of influences to process
			influences.insert(std::end(influences), std::begin(bodyInfluences), std::end(bodyInfluences));
		}
    }

    void Environment::applyEndogenous(const time::TimeManager& manager)
    {
        // Apply endogenous process to each one
		for (std::unordered_map<core::uuid::Uuid, environment::objects::BodyShPtr>::const_iterator bodiesIterator = m_bodies.cbegin();
			bodiesIterator != m_bodies.cend();
			++bodiesIterator)
        {
			bodiesIterator->second->applyEndogenous(manager);
		}
		// Apply endogenous process to each one
		for (std::unordered_map<core::uuid::Uuid, environment::objects::EnvironmentalObjectShPtr>::const_iterator objectsIterator = m_objects.cbegin();
			objectsIterator != m_objects.cend();
			++objectsIterator)
        {
			objectsIterator->second->applyEndogenous(manager);
		}
    }

    void Environment::computePerceptionsForBody(environment::objects::Body& body)
    {
        const environment::objects::frustum::Frustum& bodyFrustum(body.getFrustum());
        std::vector<environment::perceptions::Perception> perceptions(computeIntersections(bodyFrustum));
        body.onPerceptionsComputed(perceptions);
    }

    std::vector<environment::perceptions::Perception> Environment::computeIntersections(const environment::objects::frustum::Frustum& frustum) const {
        std::vector<environment::perceptions::Perception> intersections;
        // Detect intersections among bodies.
		for (std::unordered_map<core::uuid::Uuid, environment::objects::BodyShPtr>::const_iterator bodiesIterator = m_bodies.cbegin();
			bodiesIterator != m_bodies.cend();
			++bodiesIterator)
        {
            if (bodiesIterator->second != nullptr && frustum.intersects(*bodiesIterator->second))
            {
                intersections.push_back(environment::perceptions::Perception(*bodiesIterator->second));
            }
		}
		// Detect intersections among objects.
		for (std::unordered_map<core::uuid::Uuid, environment::objects::EnvironmentalObjectShPtr>::const_iterator objectsIterator = m_objects.cbegin();
			objectsIterator != m_objects.cend();
			++objectsIterator)
        {
            if (objectsIterator->second != nullptr && frustum.intersects(*objectsIterator->second))
            {
                intersections.push_back(environment::perceptions::Perception(*objectsIterator->second));
            }
		}
        // Return the built-in list of intersected objects/bodies
        return intersections;
    }
}
