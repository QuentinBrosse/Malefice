// Client Version

#include "PositionSystem.h"
#include "Position.h"
#include "AScene.h"
#include "GraphicUtil.h"

namespace ecs
{

	void PositionSystem::update(Entity& entity)
	{
		Position*	position;
		AScene*		scene;

		if ((position = dynamic_cast<Position*>(entity[POSITION])) != nullptr && (scene = dynamic_cast<AScene*>(entity[SCENE])) != nullptr)
		{
			// TODO : Offset
			scene->setPosition(*position);
		}
	}

}