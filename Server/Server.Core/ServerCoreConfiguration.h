#pragma once

#include <ostream>
#include <string>
#include <tinyxml2.h>
#include "AConfiguration.h"

class ServerCoreConfiguration : public AConfiguration
{
public:
	static const std::string	DEFAULT_SETTINGS_FILENAME;
	static const std::string	DEFAULT_SETTINGS_BACKUP_EXT;
	static const std::string	DEFAULT_NAME;
	static const std::string	DEFAULT_PASSWORD;
	static const std::string	DEFAULT_ADDRESS;
	static const short			DEFAULT_PORT;

	ServerCoreConfiguration();
	virtual ~ServerCoreConfiguration()	= default;


	virtual bool	loadFromFile(const std::string& filepath);
	virtual bool	saveToFile(const std::string& filepath)	const;


	const std::string&	getName()		const;
	const std::string&	getPassword()	const;
	const std::string&	getAddress()	const;
	short				getPort()		const;

	void	setName(const std::string& name);
	void	setPassword(const std::string& password);
	void	setAddress(const std::string& address);
	void	setPort(short port);


private:
	std::string	m_name;
	std::string	m_password;
	std::string	m_address;
	int			m_port;
};

std::ostream&	operator<<(std::ostream& os, const ServerCoreConfiguration& rhs);
