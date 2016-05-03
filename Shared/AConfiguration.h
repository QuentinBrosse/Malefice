#pragma once

#include <string>
#include <tinyxml2.h>

class AConfiguration
{
public:
	AConfiguration()			= default;
	virtual ~AConfiguration()	= default;

	virtual bool	loadFromFile(const std::string& filepath)			= 0;
	virtual bool	saveToFile(const std::string& filepath)		const	= 0;


protected:
	tinyxml2::XMLElement*	getOrCreateElement(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode& parentNode, const std::string& elementName)											const;
	std::string				getOrCreateElementString(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode& parentNode, const std::string& elementName, const std::string& defaultValue)	const;
};
