#include <iostream>
#include <easylogging++.h>
#include "ServerCore.h"
#include "ProjectGlobals.h"
#include "ServerCoreConfiguration.h"

ServerCore::ServerCore() :
	m_name(""), m_password(""), m_address(""), m_port(0), m_isActive(true), m_configuration(), m_networkModule(nullptr)
{
}


void	ServerCore::run()
{
	LOG(INFO) << "Server started";
	if (this->init() == false)
	{
		LOG(FATAL) << "Server initialization failed. Abortring." << std::endl;
		return;
	}
	while (this->isActive())
	{
		this->pulse();
	}
	LOG(INFO) << "Server stopped";
}


bool	ServerCore::init(void)
{
	if (m_configuration.loadFromFile(ServerCoreConfiguration::DEFAULT_SETTINGS_FILENAME) == false)
		return false;
	m_name = m_configuration.getName();
	m_password = m_configuration.getPassword();
	m_address = m_configuration.getAddress();
	m_port = m_configuration.getPort();
	m_networkModule = new NetworkModule();
	if (m_networkModule->init(m_address, m_port, m_password) == false)
	{
		LOG(FATAL) << "Failed to start Network Module.";
		return false;
	}
	this->displayHeader();
	return true;
}

void	ServerCore::displayHeader()	const
{
	std::string	title = ProjectGlobals::GAME_NAME + " v." + ProjectGlobals::GAME_SERVER_VERSION;

#ifdef WIN32
	SetConsoleTitle((ProjectGlobals::GAME_NAME + " v." + ProjectGlobals::GAME_SERVER_VERSION).c_str());
#endif

	std::cout << "==============================================================" << std::endl;
	std::cout << "                         " << title << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "=Server Name	: " << m_name << std::endl;
	std::cout << "=Server Port	: " << m_port << std::endl;
	std::cout << "=Max Players	: " << ProjectGlobals::MAX_PLAYERS_NB << std::endl;
	std::cout << "=Password	: " << this->m_password << std::endl;
	std::cout << "==============================================================" << std::endl;

}

void	ServerCore::pulse(void)
{
	if (m_networkModule != nullptr)
		m_networkModule->pulse();
}



bool	ServerCore::isActive()	const
{
	return m_isActive;
}

NetworkModule	*ServerCore::getNetworkModule()	const
{
	return m_networkModule;
}


void	ServerCore::setIsActive(bool isActive)
{
	m_isActive = isActive;
}
