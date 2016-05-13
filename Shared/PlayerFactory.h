#pragma once

#include "ObjectFactory.h"
#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT PlayerFactory
{
public:
	PlayerFactory()		= delete;
	~PlayerFactory()	= delete;

	static ecs::Entity*	createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId, const int team, int life);
	static ecs::Entity*	createPlayer(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId, const int team, int life);

	static ecs::Entity*	createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId);
	static ecs::Entity*	createPredator(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId);

};
