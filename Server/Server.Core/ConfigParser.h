#pragma once

#include "../../Shared/StdInc.h"

class ConfigParser
{
private:
	std::string		m_sFileName;
public:
	ConfigParser(std::string);
	~ConfigParser();

	bool			Init(void);

	std::string		GetValue(std::string);
};