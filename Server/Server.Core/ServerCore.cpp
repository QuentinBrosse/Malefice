
#include "ServerCore.h"

ServerCore::ServerCore() :
	m_sName(""),
	m_sPort(""),
	m_sPassword(""),
	m_bActive(true),
	m_cConfigParser(FILE_SETTINGS)
{
}

/*
Init of RakNet and other libraries
Return false if fail
*/
bool	ServerCore::Init(void)
{
	if (m_cConfigParser.init() == false)
		return (false);

	this->m_sName = m_cConfigParser.get("name");
	this->m_sPort = m_cConfigParser.get("port");
	this->m_sAddress = m_cConfigParser.get("address");
	this->m_sPassword = m_cConfigParser.get("password");

	if (this->m_sName.length() <= 0)
		return false;

	if (this->m_sPort.length() <= 0)
		return false;

	/* Network init */
	m_pNModule = new NetworkModule;
	if (m_pNModule->Init(this->m_sPort, this->m_sAddress, this->m_sPassword) == false)
		std::cerr << "Failed to start RakNet" << std::endl;

	/* Server Title */
	std::string title = std::string(GAME_NAME).append(" v").append(GAME_VERSION);

#ifdef WIN32
	SetConsoleTitle(title.c_str());
#endif

	/* Finished init, dump informations */
	std::cout << "==============================================================" << std::endl;
	std::cout << "                         " << title << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "=Server Name	: " << this->m_sName << std::endl;
	std::cout << "=Server Port	: " << this->m_sPort << std::endl;
	std::cout << "=Max Players	: " << MAX_PLAYERS << std::endl;
	if (this->m_sPassword.length() > 0)
		std::cout << "=Password	: " << this->m_sPassword << std::endl;
	std::cout << "==============================================================" << std::endl;
	return (true);
}

/*
Program main loop
*/
void	ServerCore::Pulse(void)
{
	if (m_pNModule)
		m_pNModule->Pulse();
}
