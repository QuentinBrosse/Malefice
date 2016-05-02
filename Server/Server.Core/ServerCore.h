#pragma once

#include <string>
#include "Singleton.h"
#include "ServerCoreConfiguration.h"
#include "NetworkModule.h"

class ServerCore : public Singleton<ServerCore>
{
	friend class Singleton<ServerCore>;

public:
	void	run();

	bool			isActive()			const;
	NetworkModule*	getNetworkModule()	const;

	void	setIsActive(bool isActive);


protected:
	ServerCore();
	~ServerCore() = default;


private:
	bool	init();
	void	pulse();
	void	displayHeader()	const;


	ServerCoreConfiguration	m_configuration;
	NetworkModule*			m_networkModule;

	bool		m_isActive;
};
