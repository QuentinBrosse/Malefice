#pragma once

#include "StdInc.h"
#include "ConfigParser.h"
#include "NetworkModule.h"
#include "Singleton.h"

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
	std::string	m_name;
	std::string	m_password;
	std::string	m_address;
	short		m_port;
	bool		m_isActive;

	ConfigParser	m_configParser;
	NetworkModule	*m_networkModule;
};
