#pragma once

#include <string>
#include <tinyxml2.h>
#include <easylogging++.h>

class ServerCoreConfiguration
{
public:
	static const std::string	DEFAULT_SETTINGS_FILENAME;
	static const std::string	DEFAULT_SETTINGS_BACKUP_EXT;
	static const std::string	DEFAULT_NAME;
	static const std::string	DEFAULT_PASSWORD;
	static const std::string	DEFAULT_ADDRESS;
	static const short			DEFAULT_PORT;

	ServerCoreConfiguration();
	~ServerCoreConfiguration()	= default;


	const std::string&	getName()		const;
	const std::string&	getPassword()	const;
	const std::string&	getAddress()	const;
	short				getPort()		const;

	void	setName(const std::string& name);
	void	setPassword(const std::string& password);
	void	setAddress(const std::string& address);
	void	setPort(short port);

	bool	loadFromFile(const std::string& filepath);
	bool	saveToFile(const std::string& filepath)	const;


private:
	tinyxml2::XMLElement*	getOrCreateElement(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode& parentNode, const std::string& elementName)											const;
	std::string				getOrCreateElementString(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode& parentNode, const std::string& elementName, const std::string& defaultValue)	const;

	std::string	m_name;
	std::string	m_password;
	std::string	m_address;
	int			m_port;
};

el::base::Writer&	operator<<(el::base::Writer& logger, const ServerCoreConfiguration& rhs);
