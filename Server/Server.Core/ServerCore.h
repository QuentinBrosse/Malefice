#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include "Singleton.h"
#include "ServerCoreConfiguration.h"
#include "NetworkModule.h"

class ServerCore : public Singleton<ServerCore>
{
	friend class Singleton<ServerCore>;

public:
	void	run();


	NetworkModule*	getNetworkModule()	const;


protected:
	ServerCore();
	~ServerCore()	= default;


private:
	bool	init();
	void	stop();
	void	pulse();
	void	displayHeader()	const;
	void	readInput();
	void	handleInput();
	void	processCommand(const std::string& command, const std::string& params);


	long long	m_startTime;
	bool		m_isActive;

	ServerCoreConfiguration	m_configuration;
	NetworkModule*			m_networkModule;

	std::queue<std::string>	m_inputQueue;
	std::mutex				m_inputMutex;
	std::atomic<bool>		m_readInput;
	std::thread				m_inputThread;
};
