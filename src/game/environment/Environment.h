#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>
#include <memory>
#include <vector>
#include "TimeManager.h"
#include "EnvironmentalObject.h"
#include "EnvironmentInitializer.h"
#include "EnvironmentListener.h"
#include "Uuid.h"
#include "EnvironmentalObjectDrawer.h"
#include "Body.h"
#include "DrawablesUpdater.h"
#include "Agent.h"
#include "Animat.h"
#include "PhysicEngine.h"

namespace environment
{
    class EnvironmentInitializer;

    class Environment
    {
        public:

            Environment();

            virtual ~Environment();

            void create(EnvironmentInitializer& initializer);

            void addListener(listener::EnvironmentListener* listener);

            void simulate(const time::TimeManager& manager);

            void spawnObject(const objects::EnvironmentalObjectShPtr object);

            void spawnAnimat(agents::AnimatShPtr animat);

            const std::vector<objects::drawable::EnvironmentalObjectDrawerShPtr>& getDrawables() const;

            environment::drawable::DrawableUpdater& getDrawablesUpdater();

        protected:

            virtual void computePerceptions();

            virtual void applyInfluences(std::vector<environment::agents::influences::InfluenceShPtr>& influences);

        private:

            void fireEnvironmentChange();

            void computePreAgentsStep(const time::TimeManager& manager);

            void computeAgentsStep(const time::TimeManager& manager);

            void computePostAgentsStep(const time::TimeManager& manager);

            void collectInfluences(std::vector<environment::agents::influences::InfluenceShPtr>& influences);

            void applyEndogenous(const time::TimeManager& manager);

            void computePerceptionsForBody(environment::objects::Body& body);

			std::vector<environment::perceptions::Perception> computeIntersections(const environment::objects::frustum::Frustum& frustum) const;

        private:

            std::unordered_map<core::uuid::Uuid, environment::objects::EnvironmentalObjectShPtr> m_objects;

            std::unordered_map<core::uuid::Uuid, environment::objects::BodyShPtr> m_bodies;
            std::unordered_map<core::uuid::Uuid, environment::agents::AgentShPtr> m_agents;
            std::vector<environment::agents::AnimatShPtr> m_animats;

            environment::physics::PhysicEngine m_physicEngine;

            std::vector<objects::drawable::EnvironmentalObjectDrawerShPtr> m_drawables;
            environment::drawable::DrawableUpdater m_updater;
            std::vector<listener::EnvironmentListener*> m_listeners;

    };
}

#endif // ENVIRONMENT_H
