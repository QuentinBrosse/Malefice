
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
	this->m_sPassword = CParser->Get("password");

	if (this->m_sName.length() <= 0)
		return (false);

	if (this->m_sPort.length() <= 0)
		return (false);

	/* Raknet init */

	return (true);
}

/*
Program main loop
*/
void	CMain::Pulse(void)
{

}