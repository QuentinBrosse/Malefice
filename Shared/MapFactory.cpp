#include "MapFactory.h"
#include "ObjectFactory.h"
#include "SceneMesh.h"
#include "NodePickable.h"

ecs::Entity* MapFactory::createMap(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner, const std::string& nameMesh, const std::string& namePK3)
{
	ecs::Entity*	map = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::MAP);

	(*map)[ecs::AComponent::ComponentType::SCENE] = new ecs::SceneMesh(device, "", nameMesh, nodePickable::IS_PICKABLE, true, namePK3);

	return map;
}
