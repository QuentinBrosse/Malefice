
#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string fileName)
{
	this->m_sFileName = fileName;
}

ConfigParser::~ConfigParser()
{

}

bool			ConfigParser::Init(void)
{

	return (true);
}

std::string		ConfigParser::GetValue(std::string value)
{
	return ("");
}