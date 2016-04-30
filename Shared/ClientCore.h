#pragma once

#include <map>
#include "Entity.h"

class ClientCore
{
public:
	ClientCore() = default;
	~ClientCore() = default;

	void	addEntity(const ecs::Entity& newEntity);
	void	deleteEntity(int id);
	void	dump()	const;

private:
	std::map<int, ecs::Entity>	m_entities;
};
