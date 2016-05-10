#pragma once

#include "Singleton.h"
#include "GraphicUtil.h"
#include "NetworkModule.h"
#include "EventReceiver.h"
#include "PlayerManager.h"
#include "SceneMesh.h"

#include <chrono>

typedef std::chrono::duration<float, std::chrono::seconds::period> fpTime;

class ClientCore : public Singleton<ClientCore>
{
	friend class Singleton<ClientCore>;

public:
	void			run();

	bool			isActive()			const;
	NetworkModule*	getNetworkModule()	const;
	GraphicUtil*	getGraphicModule()	const;
	PlayerManager*	getPlayerManager()	const;

	void			setIsActive(bool isActive);

protected:
	ClientCore();
	~ClientCore();

private:
	bool	init();
	void	pulse();

	NetworkModule*	m_networkModule;
	GraphicUtil*	m_graphicModule;
	PlayerManager*	m_playerManager;
	ecs::SceneMesh*	m_map;
	bool			m_isActive;
	

	std::chrono::high_resolution_clock::time_point m_lastTime = std::chrono::high_resolution_clock::now();
};
