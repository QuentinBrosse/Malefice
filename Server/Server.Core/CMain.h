#pragma once

#include "../../Shared/StdInc.h"

#include "ConfigParser.h"

class CMain : public ExplicitSingleton<CMain>
{
private:
	std::string		m_sName;
	std::string		m_sPort;
	std::string		m_sPassword;
	bool			m_bActive;

public:
	CMain();
	~CMain();

	bool			Init(void);
	void			Pulse(void);

	bool			IsActive(void) { return m_bActive; }
	void			SetActive(bool active) { m_bActive = active; }
};
