#pragma once

#include "ObjectFactory.h"
#include "Team.h"
#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT PlayerFactory
{
public:
	PlayerFactory()		= delete;
	~PlayerFactory()	= delete;

	static ecs::Entity*	createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, ecs::Team::TeamType team, int life);
	static ecs::Entity * createPlayer(ecs::ClientId id, const irr::core::vector3df & vectorPosition, const irr::core::vector3df & vectorRotation, ecs::Team::TeamType team, const int life);

	static ecs::Entity*	createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation);
	static ecs::Entity * createPredator(ecs::ClientId id, const irr::core::vector3df & vectorPosition, const irr::core::vector3df & vectorRotation);

};
