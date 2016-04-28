#pragma once

#include <tinyxml2.h>
#include "../../Shared/StdInc.h"

class ConfigParser
{
public:
	ConfigParser(const std::string& fileName);
	~ConfigParser() = default;

	bool		init();
	bool		save();
	void		loadDefault(const std::string& name, const std::string& value);
	void		loadDefaults();
	bool		exists(const std::string& name);
	void		set(const std::string& name, const std::string& value);
	std::string	get(const std::string& name);


private:
	tinyxml2::XMLNode* findNode(tinyxml2::XMLNode* node, const std::string& name);

	std::string				m_sFileName;
	tinyxml2::XMLDocument	m_xml;
	tinyxml2::XMLNode*		m_pRootElement;
};
