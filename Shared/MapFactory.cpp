#include "MapFactory.h"
#include "ObjectFactory.h"
#include "SceneMesh.h"
#include "NodePickable.h"

ecs::Entity* MapFactory::createMap(irr::IrrlichtDevice* device, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::NetworkID netID, const std::string& nameMesh, const std::string& namePK3)
{
	ecs::Entity*	map = ObjectFactory::createObject(vectorPosition, vectorRotation, netID);

	(*map)[ecs::SCENE] = new ecs::SceneMesh(device, "", nameMesh, nodePickable::IS_PICKABLE, namePK3);

	return map;
}
