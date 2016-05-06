#include "ClientCore.h"
#include "Logger.h"

ClientCore::ClientCore() :
	m_networkModule(nullptr), m_isActive(true)
{
}

ClientCore::~ClientCore()
{
	if (m_networkModule->isConnected())
		m_networkModule->disconnect();
}

void	ClientCore::run()
{
	LOG_INFO << "Client started.";
	if (this->init() == false)
	{
		LOG_CRITICAL << "Client initialization failed. Abortring.";
		return;
	}
	LOG_INFO << "Client initialized.";
	while (this->isActive())
	{
		this->pulse();
	}
	LOG_INFO << "Client stopped.";
}

bool	ClientCore::init()
{
	m_networkModule = new NetworkModule();
	if (m_networkModule->init() == false)
	{
		LOG_CRITICAL << "Failed to start Network Module.";
		return false;
	}
	if (m_networkModule->connect("10.37.152.144", 1234, ""))
		LOG_INFO << "Connected !";
	else
		LOG_INFO << "Unable to connect !";
}

void	ClientCore::pulse()
{
	if (m_networkModule != nullptr && m_networkModule->isConnected())
		m_networkModule->pulse();
}

bool	ClientCore::isActive()	const
{
	return m_isActive;
}

NetworkModule	*ClientCore::getNetworkModule()	const
{
	return m_networkModule;
}


void	ClientCore::setIsActive(bool isActive)
{
	m_isActive = isActive;
}
