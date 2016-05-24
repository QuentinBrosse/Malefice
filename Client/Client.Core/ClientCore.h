#pragma once

#include <chrono>
#include <RPC3.h>
#include "Singleton.h"
#include "GraphicUtil.h"
#include "NetworkModule.h"
#include "EventReceiver.h"
#include "PlayerManager.h"
#include "MasterList.h"
#include "SceneMesh.h"

typedef std::chrono::duration<float, std::chrono::seconds::period> fpTime;

class ClientCore : public Singleton<ClientCore>, public NetworkObject
{
	friend class Singleton<ClientCore>;

public:
	void	createEntities();
	void			run();

	NetworkModule*	getNetworkModule()	const;
	GraphicUtil*	getGraphicModule()	const;
	PlayerManager*	getPlayerManager()	const;
	MasterList*		getMasterList()		const;
	ecs::ClientId	getClientId()		const;
	bool			isActive()			const;
	ecs::Entity*	getMap()			const;

	void	setIsActive(bool isActive);
	void	setNickname(const std::string& nickname);


	void	setClientId(ecs::ClientId clientId, RakNet::RPC3* rpc);
	void	notifyInvalidNickname(RakNet::RPC3* rpc);
	void	startGame(RakNet::RPC3* rpc);


protected:
	ClientCore();
	~ClientCore();

private:
	bool	init();
	void	pulse();

	NetworkModule*	m_networkModule;
	GraphicUtil*	m_graphicModule;
	PlayerManager*	m_playerManager;
	MasterList*		m_masterList;
	ecs::ClientId	m_clientId;
	std::string		m_nickname;
	bool			m_isActive;

	// Local Test
	ecs::Entity*				m_map;
	ecs::Entity*				m_player;
	ecs::Entity*				m_player_ia;

	std::chrono::high_resolution_clock::time_point m_lastTime = std::chrono::high_resolution_clock::now();
};
