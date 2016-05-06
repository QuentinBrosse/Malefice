#include <string>
#include <fstream>
#include <tinyxml2.h>
#include "ServerCoreConfiguration.h"
#include "ProjectGlobals.h"
#include "Logger.h"

const std::string	ServerCoreConfiguration::DEFAULT_SETTINGS_FILENAME		= "settings.xml";
const std::string	ServerCoreConfiguration::DEFAULT_SETTINGS_BACKUP_EXT	= ".bak";
const std::string	ServerCoreConfiguration::DEFAULT_NAME					= ProjectGlobals::GAME_NAME + " Server";
const std::string	ServerCoreConfiguration::DEFAULT_PASSWORD				= "";
const std::string	ServerCoreConfiguration::DEFAULT_ADDRESS				= "127.0.0.1";
const short			ServerCoreConfiguration::DEFAULT_PORT					= 2504;

ServerCoreConfiguration::ServerCoreConfiguration() :
	m_name(ServerCoreConfiguration::DEFAULT_NAME),
	m_password(ServerCoreConfiguration::DEFAULT_PASSWORD),
	m_address(ServerCoreConfiguration::DEFAULT_ADDRESS),
	m_port(ServerCoreConfiguration::DEFAULT_PORT)
{
}


bool	ServerCoreConfiguration::loadFromFile(const std::string& filepath)
{
	tinyxml2::XMLDocument	doc;
	tinyxml2::XMLElement*	serverElement;
	tinyxml2::XMLError		loadResult = doc.LoadFile(filepath.c_str());

	if (loadResult != tinyxml2::XMLError::XML_SUCCESS)
	{
		LOG_ERROR << "Server configuration file could not be read properly (error code: " << loadResult << ").";

		if (loadResult != tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND)
		{
			std::ifstream	currentFile(filepath, std::ios_base::in);
			std::ofstream	backupFile(filepath + ServerCoreConfiguration::DEFAULT_SETTINGS_BACKUP_EXT, std::ios_base::out | std::ios_base::app);

			if (!currentFile.is_open() || !backupFile.is_open())
			{
				LOG_CRITICAL << "Could not create server configuration backup. Giving up.";
				return false;
			}
			backupFile << currentFile.rdbuf();
			backupFile.close();
			currentFile.close();
		}
		if (this->saveToFile(filepath) == true)
		{
			LOG_INFO << "Server configuration file was reset to default settings (backup is in " << (filepath + ServerCoreConfiguration::DEFAULT_SETTINGS_BACKUP_EXT) << ").";
			LOG_WARNING << "Server will be running with default settings (" << *this << ").";
		}
		return true;
	}
	serverElement = this->getOrCreateElement(doc, doc, "server");
	m_name = this->getOrCreateElementString(doc, *serverElement, "name", ServerCoreConfiguration::DEFAULT_NAME);
	m_password = this->getOrCreateElementString(doc, *serverElement, "password", ServerCoreConfiguration::DEFAULT_PASSWORD);
	m_address = this->getOrCreateElementString(doc, *serverElement, "address", ServerCoreConfiguration::DEFAULT_ADDRESS);
	m_port = std::stoi(this->getOrCreateElementString(doc, *serverElement, "port", std::to_string(ServerCoreConfiguration::DEFAULT_PORT)));
	if (m_port < 0 || m_port > 65535)
	{
		LOG_WARNING << "Port must be an integer between 0 and 65535. Default port (" << ServerCoreConfiguration::DEFAULT_PORT << ") will be used.";
		m_port = ServerCoreConfiguration::DEFAULT_PORT;
	}
	this->saveToFile(filepath); // TODO: save only if XML changed
	return true;
}

bool	ServerCoreConfiguration::saveToFile(const std::string& filepath)	const
{
	tinyxml2::XMLDocument	doc;
	tinyxml2::XMLError		saveResult = tinyxml2::XMLError::XML_ERROR_COUNT;
	tinyxml2::XMLElement*	serverElement = this->getOrCreateElement(doc, doc, "server");

	this->getOrCreateElement(doc, *serverElement, "name")->SetText(m_name.c_str());
	this->getOrCreateElement(doc, *serverElement, "password")->SetText(m_password.c_str());
	this->getOrCreateElement(doc, *serverElement, "address")->SetText(m_address.c_str());
	this->getOrCreateElement(doc, *serverElement, "port")->SetText(std::to_string(m_port).c_str());
	saveResult = doc.SaveFile(filepath.c_str());
	if (saveResult != tinyxml2::XMLError::XML_SUCCESS)
	{
		LOG_ERROR << "Server configuration file could not be saved (error code: " << saveResult << ").";
		return false;
	}
	LOG_INFO << "Configuration file was saved to " << filepath << ".";
	return true;
}


const std::string&	ServerCoreConfiguration::getName()		const
{
	return m_name;
}

const std::string&	ServerCoreConfiguration::getPassword()	const
{
	return m_password;
}

const std::string&	ServerCoreConfiguration::getAddress()	const
{
	return m_address;
}

short				ServerCoreConfiguration::getPort()		const
{
	return m_port;
}


void	ServerCoreConfiguration::setName(const std::string& name)
{
	m_name = name;
}

void	ServerCoreConfiguration::setPassword(const std::string& password)
{
	m_password = password;
}

void	ServerCoreConfiguration::setAddress(const std::string& address)
{
	m_address = address;
}

void	ServerCoreConfiguration::setPort(short port)
{
	m_port = port;
}



std::ostream&	operator<<(std::ostream& os, const ServerCoreConfiguration& rhs)
{
	os << "ServerCoreConfiguration {name = \"" << rhs.getName() << "\", password = \"" << rhs.getPassword() << "\", address = \"" << rhs.getAddress() << "\", port = " << rhs.getPort() << "}";
	return os;
}
