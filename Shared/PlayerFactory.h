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

	static ecs::Entity*	createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId id, const ecs::Position position, ecs::Team::TeamType team);

	static void			initNicknameNode(ecs::Entity* entity, irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent);

	static void			initScene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::Entity& entity);
	static void			initPredatorScene(irr::IrrlichtDevice* device, const std::string& newNameMesh, ecs::Entity& entity);

	static ecs::Entity*	createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId id, const ecs::Position position);
};
