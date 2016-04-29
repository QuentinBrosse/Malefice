#include "ServerCore.h"

ServerCore::ServerCore() :
	m_name(""), m_password(""), m_address(""), m_port(0), m_isActive(true), m_configParser(FILE_SETTINGS), m_networkModule(nullptr)
{
}

bool	ServerCore::init(void)
{
	if (m_configParser.init() == false)
		return false;
	m_name = m_configParser.get("name");
	m_password = m_configParser.get("password");
	m_address = m_configParser.get("address");
	m_port = std::stoi(m_configParser.get("port"));
	if (this->m_name.length() == 0 || m_address.length() == 0 || m_port == 0 || m_port > 65535)
		return false;
	m_networkModule = new NetworkModule();
	if (m_networkModule->init(m_address, m_port, m_password) == false)
		std::cerr << "Failed to start RakNet" << std::endl;

	std::string title = std::string(GAME_NAME).append(" v").append(GAME_VERSION);

#ifdef WIN32
	SetConsoleTitle(title.c_str());
#endif

	std::cout << "==============================================================" << std::endl;
	std::cout << "                         " << title << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "=Server Name	: " << this->m_name << std::endl;
	std::cout << "=Server Port	: " << this->m_port << std::endl;
	std::cout << "=Max Players	: " << MAX_PLAYERS << std::endl;
	if (this->m_password.length() > 0)
		std::cout << "=Password	: " << this->m_password << std::endl;
	std::cout << "==============================================================" << std::endl;
	return (true);
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
