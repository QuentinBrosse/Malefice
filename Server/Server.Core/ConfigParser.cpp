
#include "ConfigParser.h"

XML								* ConfigParser::m_pXML = NULL;
XMLNode							* ConfigParser::m_pRootNode = NULL;
bool							ConfigParser::m_bOpen = false;

ConfigParser::ConfigParser(std::string fileName)
{
	this->m_sFileName = fileName;
	this->m_bOpen = false;
}

ConfigParser::~ConfigParser()
{
}

bool			ConfigParser::Init(void)
{
	m_pXML = new XML(this->m_sFileName.c_str());

	if (m_pXML == false)
		return (false);

	m_bOpen = true;

	m_pRootNode = m_pXML->GetRootNode();

	if (m_pRootNode == false)
		m_pRootNode = m_pXML->CreateRootNode("server");

	LoadDefaults();

	this->Save();

	return (true);
}

void			ConfigParser::LoadDefaults(void)
{
	DEFAULT("name", FILE_SETTINGS_D_NAME);
	DEFAULT("address", FILE_SETTINGS_D_ADDRESS);
	DEFAULT("port", FILE_SETTINGS_D_PORT);
	DEFAULT("password", FILE_SETTINGS_D_PASSWORD);
}

bool ConfigParser::Exists(std::string szName)
{
	if (!m_pRootNode)
		return (false);

	return (m_pRootNode->FindNode(szName.c_str()) != NULL);
}

void ConfigParser::Set(std::string szName, std::string szValue)
{
	XMLNode * pRootNode = m_pXML->GetRootNode();

	if (pRootNode)
	{
		XMLNode * pSubNode = pRootNode->FindNode(szName.c_str());

		if (!pSubNode)
			pSubNode = pRootNode->CreateSubNode(szName.c_str());

		pSubNode->SetValue(szValue.c_str());
	}

	Save();
}

std::string ConfigParser::Get(std::string szName)
{
	XMLNode * pRootNode = m_pXML->GetRootNode();

	if (pRootNode)
	{
		XMLNode * pSubNode = pRootNode->FindNode(szName.c_str());

		if (pSubNode && pSubNode->GetValue() != NULL)
		{
			return (pSubNode->GetValue());
		}
	}
	return ("");
}

bool			ConfigParser::Save(void)
{
	if (m_pXML == false)
		return (false);

	return (m_pXML->Save());
}