#pragma once

#include "Entity.h"

namespace factory
{
	ecs::Entity& player(ecs::Entity& entity, networkID network_id, int team);
	ecs::Entity& predator(ecs::Entity& entity, networkID network_id);
}