
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

bool	CMain::Init(void)
{
	return (true);
}