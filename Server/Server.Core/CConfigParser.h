#pragma once

#include "../../Shared/StdInc.h"

class CConfigParser
{
private:
	std::string		m_sFileName;
public:
	CConfigParser(std::string);
	~CConfigParser();

	bool			Init(void);

	std::string		GetValue(std::string);
};