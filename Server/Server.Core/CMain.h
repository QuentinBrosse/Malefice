#pragma once

#include "../../Shared/StdInc.h"

class CMain : public ExplicitSingleton<CMain>
{
private:
	std::string		m_sName;
	int				m_iPort;
	bool			m_bActive;

public:
	CMain(std::string, int);
	~CMain();

	bool			Init(void);
	void			Pulse(void);

	bool			IsActive(void) { return m_bActive; }
	void			SetActive(bool active) { m_bActive = active; }
};
