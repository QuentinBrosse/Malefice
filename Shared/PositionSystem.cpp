#include "PositionSystem.h"
#include "Position.h"
#include "AScene.h"

namespace ecs
{

	void PositionSystem::update(Entity& entity)
	{
		Position*	position;
		AScene*		scene;

		if ((position = dynamic_cast<Position*>(entity[POSITION])) != nullptr && (scene = dynamic_cast<AScene*>(entity[SCENE])) != nullptr)
		{
			scene->setPosition(*position);
		}
	}

}