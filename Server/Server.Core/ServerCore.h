#pragma once

#include <string>
#include "Singleton.h"
#include "ConfigParser.h"
#include "NetworkModule.h"

class ServerCore : public Singleton<ServerCore>
{
	friend class Singleton<ServerCore>;

public:
	void	run();

	bool			isActive()			const;
	NetworkModule*	getNetworkModule()	const;

	void	setIsActive(bool isActive);


protected:
	ServerCore();
	~ServerCore() = default;


private:
	bool	init();
	void	displayHeader()	const;
	void	pulse();


	std::string	m_name;
	std::string	m_password;
	std::string	m_address;
	int			m_port;
	bool		m_isActive;

	ConfigParser	m_configParser;
	NetworkModule	*m_networkModule;
};
