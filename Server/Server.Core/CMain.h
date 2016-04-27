#pragma once

#include "../../Shared/StdInc.h"

#include "ConfigParser.h"
#include "NetworkModule.h"

class CMain : public ExplicitSingleton<CMain>
{
private:
	std::string		m_sName;
	std::string		m_sPort;
	std::string		m_sPassword;
	std::string		m_sAddress;
	bool			m_bActive;

	ConfigParser	*CParser;
	NetworkModule	*NModule;

public:
	CMain();
	~CMain();

	bool			Init(void);
	void			Pulse(void);

	bool			IsActive(void) { return m_bActive; }
	void			SetActive(bool active) { m_bActive = active; }
};
