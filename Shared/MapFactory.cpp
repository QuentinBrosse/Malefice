#include "MapFactory.h"
#include "ObjectFactory.h"
#include "CollectionComponent.h"

ecs::Entity* MapFactory::createMap(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::NetworkID netID, const std::string& nameMesh, const std::string& namePK3)
{
	ecs::Entity*	map = ObjectFactory::createObject(vectorPosition, vectorRotation, netID);



	return map;
}
