
#include "CConfigParser.h"

CConfigParser::CConfigParser(std::string fileName)
{
	this->m_sFileName = fileName;
}

CConfigParser::~CConfigParser()
{

}

bool			CConfigParser::Init(void)
{

	return (true);
}

std::string		CConfigParser::GetValue(std::string value)
{
	return ("");
}