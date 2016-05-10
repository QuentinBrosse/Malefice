#pragma once

#include "ObjectFactory.h"
#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT PlayerFactory
{
public:
	PlayerFactory()		= delete;
	~PlayerFactory()	= delete;

	static ecs::Entity *createPlayer(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId, const int team, int life);
	static ecs::Entity *createPredator(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId);
};
