#pragma once

#include "../../Shared/StdInc.h"

#include "../../Shared/XML.h"

#define DEFAULT(__x,__y)	if(!Exists(__x)) Set(__x, __y)

class ConfigParser
{
private:
	std::string			m_sFileName;

	static	XML			* m_pXML;
	static	XMLNode		* m_pRootNode;

	static	bool		m_bOpen;
public:
	ConfigParser(std::string);
	~ConfigParser();

	bool			Init(void);
	bool			Save(void);
	void			LoadDefaults(void);
	bool			Exists(std::string);
	void			Set(std::string, std::string);
	std::string		Get(std::string);
};