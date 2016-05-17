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

}