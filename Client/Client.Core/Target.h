#pragma once

#include <Singleton.h>
#include "SceneBillboard.h"
#include "Position.h"
#include "GraphicUtil.h"
#include "PlayerManager.h"
#include "WeaponManager.h"

class Target : public Singleton<Target>
{
	friend class Singleton<Target>;

protected:
	Target();
	~Target();

public:
	void						refresh();
	void						debugDrawRay()	const;
	const irr::core::line3df&	getRay()		const;

private:
	GraphicUtil*			m_graphicUtil;
	ecs::SceneBillboard*	m_scene;
	irr::core::line3df		m_ray;
	PlayerManager*			m_playerManager;
};