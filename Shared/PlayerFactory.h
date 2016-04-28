#pragma once

#include "Entity.h"

namespace factory
{
	ecs::Entity& player(ecs::Entity& entity, int team);
	ecs::Entity& predator(ecs::Entity& entity);
}