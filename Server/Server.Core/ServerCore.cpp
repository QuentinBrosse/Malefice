#include <iostream>
#include <easylogging++.h>
#include "ServerCore.h"
#include "ProjectGlobals.h"
#include "ServerCoreConfiguration.h"

ServerCore::ServerCore() :
	m_configuration(), m_networkModule(nullptr), m_isActive(true)
{
}


void	ServerCore::run()
{
	LOG(INFO) << "Server started.";
	if (this->init() == false)
	{
		LOG(FATAL) << "Server initialization failed. Abortring." << std::endl;
		return;
	}
	LOG(INFO) << "Server initialized.";
	while (this->isActive())
	{
		this->pulse();
	}
	LOG(INFO) << "Server stopped.";
}


bool	ServerCore::init()
{
	if (m_configuration.loadFromFile(ServerCoreConfiguration::DEFAULT_SETTINGS_FILENAME) == false)
		return false;
	m_networkModule = new NetworkModule();
	if (m_networkModule->init(m_configuration.getAddress(), m_configuration.getPort(), m_configuration.getPassword()) == false)
	{
		LOG(FATAL) << "Failed to start Network Module.";
		return false;
	}
	this->displayHeader();
	return true;
}

void	ServerCore::pulse()
{
	if (m_networkModule != nullptr)
		m_networkModule->pulse();
}

void	ServerCore::displayHeader()	const
{
	std::string	title = ProjectGlobals::GAME_NAME + " v." + ProjectGlobals::GAME_SERVER_VERSION;

#ifdef WIN32
	SetConsoleTitle(title.c_str());
#endif

	std::cout << "==============================================================" << std::endl;
	std::cout << "                         " << title << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "=Server Name	: " << m_configuration.getName() << std::endl;
	std::cout << "=Server Port	: " << m_configuration.getPort() << std::endl;
	std::cout << "=Max Players	: " << ProjectGlobals::MAX_PLAYERS_NB << std::endl;
	std::cout << "=Password	: " << m_configuration.getPassword() << std::endl;
	std::cout << "==============================================================" << std::endl;

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
