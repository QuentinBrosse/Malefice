#include "ConfigParser.h"
#include "ProjectGlobals.h"

ConfigParser::ConfigParser(const std::string& fileName) :
	m_sFileName(fileName),
	m_xml(),
	m_pRootElement(nullptr)
{
}

bool ConfigParser::init()
{
	tinyxml2::XMLError loadResult = m_xml.LoadFile(this->m_sFileName.c_str());

	if (loadResult == tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND || loadResult == tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED)
		return false;
	m_pRootElement = m_xml.RootElement();
	if (m_pRootElement == nullptr)
	{
		m_pRootElement = m_xml.NewElement("server");
		m_xml.InsertFirstChild(m_pRootElement);
	}
	this->loadDefaults();
	this->save();
	return true;
}

void ConfigParser::loadDefault(const std::string& name, const std::string& value)
{
	if (!this->exists(name))
		this->set(name, value);
}

void ConfigParser::loadDefaults()
{
	this->loadDefault("name", ProjectGlobals::GAME_SERVER_DEFAULT_NAME);
	this->loadDefault("address", ProjectGlobals::GAME_SERVER_DEFAULT_ADDRESS);
	this->loadDefault("port", std::to_string(ProjectGlobals::GAME_SERVER_DEFAULT_PORT));
	this->loadDefault("password", ProjectGlobals::GAME_SERVER_DEFAULT_PASSWORD);
}

bool ConfigParser::exists(const std::string& name)
{
	if (!m_pRootElement)
		return false;
	return (this->findNode(m_pRootElement, name.c_str()) != nullptr);
}

void ConfigParser::set(const std::string &name, const std::string& value)
{
	tinyxml2::XMLNode* rootNode = m_xml.RootElement();

	if (rootNode != nullptr)
	{
		tinyxml2::XMLNode* subNode = this->findNode(rootNode, name);

		if (subNode == nullptr)
		{
			subNode = m_xml.NewElement(name.c_str());
			rootNode->InsertEndChild(subNode);
		}

		subNode->ToElement()->SetText(value.c_str());
	}

	this->save();
}

std::string ConfigParser::get(const std::string& name)
{
	tinyxml2::XMLNode* pRootNode = m_xml.RootElement();

	if (pRootNode)
	{
		tinyxml2::XMLNode* pSubNode = this->findNode(pRootNode, name);

		if (pSubNode != nullptr && pSubNode->ToElement() != nullptr && pSubNode->ToElement()->GetText() != nullptr)
			return (pSubNode->ToElement()->GetText());
	}

	return "";
}

bool ConfigParser::save(void)
{
	return m_xml.SaveFile(m_sFileName.c_str()) == tinyxml2::XMLError::XML_SUCCESS;
}

tinyxml2::XMLNode* ConfigParser::findNode(tinyxml2::XMLNode* node, const std::string& name)
{
	if (node == nullptr)
		return nullptr;
	if (node->Value() == name)
		return node;
	for (auto currentNode = node->FirstChildElement(); currentNode != nullptr; currentNode = currentNode->NextSiblingElement())
	{
		if (currentNode->Value() == name)
			return currentNode;
		tinyxml2::XMLNode* ret = this->findNode(currentNode->FirstChildElement(), name);

		if (ret != nullptr)
			return ret;
	}
	return nullptr;
}
