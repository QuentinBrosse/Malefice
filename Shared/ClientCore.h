#pragma once

#include <map>
#include "Entity.h"
#include "MovementSystem.h"
#include "WeaponSystem.h"
#include "SpellSystem.h"

class ClientCore
{
public:
	ClientCore() = default;
	~ClientCore() = default;

	void	addEntity(ecs::Entity& newEntity);
	void	deleteEntity(int id);
	void	dump()	const;
	void	run();
private:
	std::map<int, ecs::Entity&>	m_entities;
};
