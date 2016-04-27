
#include "CMain.h"

CMain::CMain(std::string sName, int iPort)
{
	this->m_sName = sName;
	this->m_iPort = iPort;
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
	return (true);
}

/*
Program main loop
*/
void	CMain::Pulse(void)
{

}