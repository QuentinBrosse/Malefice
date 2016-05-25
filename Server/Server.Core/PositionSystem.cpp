// Server Version

#include "PositionSystem.h"
#include "Position.h"
#include "AScene.h"

namespace ecs
{

	void PositionSystem::update(Entity& entity)
	{
		Position*	position;
		AScene*		scene;

		if ((position = dynamic_cast<Position*>(entity[ecs::AComponent::ComponentType::POSITION])) != nullptr && (scene = dynamic_cast<AScene*>(entity[ecs::AComponent::ComponentType::SCENE])) != nullptr)
		{
			// TODO: remove or update entity's position to others?
		}
	}

	void	PositionSystem::updateScenePosition(Entity& entity)
	{
		ecs::Position*	position;
		ecs::AScene*	scene;

		if ((position = dynamic_cast<ecs::Position*>(entity[ecs::AComponent::ComponentType::POSITION])) != nullptr && (scene = dynamic_cast<ecs::AScene*>(entity[ecs::AComponent::ComponentType::SCENE])) != nullptr)
		{
			scene->setPosition(*position);
		}
	}
}