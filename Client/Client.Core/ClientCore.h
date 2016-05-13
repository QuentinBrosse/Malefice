#pragma once

#include "Singleton.h"
#include "GraphicUtil.h"
#include "NetworkModule.h"
#include "EventReceiver.h"
#include "PlayerManager.h"
#include "SceneMesh.h"

#include <chrono>

typedef std::chrono::duration<float, std::chrono::seconds::period> fpTime;

class ClientCore : public Singleton<ClientCore>, public NetworkObject
{
	friend class Singleton<ClientCore>;

public:
	void			run();

	bool			isActive()			const;
	NetworkModule*	getNetworkModule()	const;
	GraphicUtil*	getGraphicModule()	const;
	PlayerManager*	getPlayerManager()	const;

	void	setIsActive(bool isActive);
	void	setClientId(ecs::ClientId clientId);

protected:
	ClientCore();
	~ClientCore();

private:
	bool	init();
	void	pulse();
	void	createEntities();

	NetworkModule*	m_networkModule;
	GraphicUtil*	m_graphicModule;
	PlayerManager*	m_playerManager;
	ecs::ClientId	m_clientId;
	bool			m_isActive;
	
	ecs::Entity*				m_map;
	std::vector<ecs::Entity*>	m_entitiesMouvable;
	ecs::Entity*				m_predator;

	std::chrono::high_resolution_clock::time_point m_lastTime = std::chrono::high_resolution_clock::now();
};
