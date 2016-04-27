
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
	ConfigParser *CParser = new ConfigParser(FILE_SETTINGS);

	if (CParser->Init() == false)
		return (false);

	this->m_sName = CParser->GetValue("name");
	this->m_sPort = CParser->GetValue("port");
	this->m_sPassword = CParser->GetValue("password");
	return (true);
}

/*
Program main loop
*/
void	CMain::Pulse(void)
{

}