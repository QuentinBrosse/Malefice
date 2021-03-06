#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include "Singleton.h"
#include "ServerCoreConfiguration.h"
#include "NetworkModule.h"
#include "PlayerManager.h"
#include "SpawnerManager.h"
#include "PhysicsUtil.h"
#include "MasterList.h"
#include "QueryServer.h"

class ServerCore : public Singleton<ServerCore>
{
	friend class Singleton<ServerCore>;

public:
	void	run();
	void	startGame();
	void	stopGame();
	bool	isActive() const;

	NetworkModule&				getNetworkModule();
	PlayerManager&				getPlayerManager();
	ServerCoreConfiguration&	getServerCoreConfiguration();
	MasterList&					getMasterList();
	PhysicsUtil&				getPhysicsUtil();

protected:
	ServerCore();
	~ServerCore()	= default;


private:
	static const unsigned int	ENTITIES_UPDATES_TICKS;

	bool	init();
	void	stop();
	void	pulse(long long elapsedTime);
	void	displayHeader()	const;
	void	readInput();
	void	handleInput();
	void	processCommand(const std::string& command, const std::string& params);
	void	createEntities();


	long long	m_startTime;
	long long	m_updateElapsedTime;
	long long	m_gameStartTime;
	long long	m_gameEndTime;
	bool		m_isActive;
	bool		m_gameStarted;

	ServerCoreConfiguration	m_configuration;
	NetworkModule			m_networkModule;
	PlayerManager			m_playerManager;
	SpawnerManager			m_spawnerManager;
	PhysicsUtil&			m_physicsUtil;
	MasterList				m_masterList;
	QueryServer				m_queryServer;

	std::queue<std::string>	m_inputQueue;
	std::mutex				m_inputMutex;
	std::atomic<bool>		m_readInput;
	std::thread				m_inputThread;
};
