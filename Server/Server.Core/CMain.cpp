
#include "CMain.h"

CMain::CMain()
{
	this->m_sName = "";
	this->m_sPort = "";
	this->m_sPassword = "";
	this->m_bActive = true;
}

CMain::~CMain()
{
}

/*
Init of RakNet and other libraries
Return false if fail
*/
bool	CMain::Init(void)
{
	/* Configuration parsing */
	CParser = new ConfigParser(FILE_SETTINGS);

	if (CParser->Init() == false)
		return (false);

	this->m_sName = CParser->Get("name");
	this->m_sPort = CParser->Get("port");
	this->m_sAddress = CParser->Get("address");
	this->m_sPassword = CParser->Get("password");

	if (this->m_sName.length() <= 0)
		return (false);

	if (this->m_sPort.length() <= 0)
		return (false);

	/* Network init */
	NModule = new NetworkModule;
	if (NModule->Init(this->m_sPort, this->m_sAddress, this->m_sPassword) == false)
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
void	CMain::Pulse(void)
{
	if (NModule)
		NModule->Pulse();
}