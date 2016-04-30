#pragma once

#include "StdInc.h"

#include "Singleton.h"
#include "ConfigParser.h"
#include "NetworkModule.h"

class ServerCore : public Singleton<ServerCore>
{
	friend class Singleton<ServerCore>;

public:
	bool	init();
	void	pulse();

	bool			isActive()			const;
	NetworkModule*	getNetworkModule()	const;

	void	setIsActive(bool isActive);


protected:
	ServerCore();
	~ServerCore() = default;


private:
	void	displayHeader()	const;


	std::string	m_name;
	std::string	m_password;
	std::string	m_address;
	int			m_port;
	bool		m_isActive;

	ConfigParser	m_configParser;
	NetworkModule	*m_networkModule;
};
