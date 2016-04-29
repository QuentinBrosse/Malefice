#pragma once

#include "Entity.h"

class ClientCore
{
public:
	ClientCore() = default;
	~ClientCore() = default;

	void	addEntity(const ecs::Entity& newEntity);
	void	deleteEntity(const int id);
	void	dump() const;

private:
	std::map<const int, ecs::Entity>	m_entityes;
};