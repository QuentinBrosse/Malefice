#pragma once

#include "../../Shared/StdInc.h"

#include "ConfigParser.h"
#include "NetworkModule.h"
#include "Singleton.h"

class ServerCore : public Singleton<ServerCore>
{
	friend class Singleton<ServerCore>;

public:
	bool			Init(void);
	void			Pulse(void);

	bool			IsActive(void) { return m_bActive; }
	void			SetActive(bool active) { m_bActive = active; }

	NetworkModule	*GetNetworkModule(void) { return m_pNModule;  }

protected:
	ServerCore();
	~ServerCore() = default;

private:
	std::string		m_sName;
	std::string		m_sPort;
	std::string		m_sPassword;
	std::string		m_sAddress;
	bool			m_bActive;

	ConfigParser	m_cConfigParser;
	NetworkModule	*m_pNModule;
};
