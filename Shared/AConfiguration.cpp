#include "AConfiguration.h"

tinyxml2::XMLElement*	AConfiguration::getOrCreateElement(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode& parentNode, const std::string& elementName)	const
{
	if (parentNode.FirstChildElement(elementName.c_str()) == nullptr)
	{
		tinyxml2::XMLElement*	element = doc.NewElement(elementName.c_str());
		parentNode.InsertEndChild(element);
	}
	return parentNode.FirstChildElement(elementName.c_str());
}

std::string	AConfiguration::getOrCreateElementString(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode& parentNode, const std::string& elementName, const std::string& defaultValue)	const
{
	if (this->getOrCreateElement(doc, parentNode, elementName)->GetText() == nullptr)
		this->getOrCreateElement(doc, parentNode, elementName)->SetText(defaultValue.c_str());
	if (this->getOrCreateElement(doc, parentNode, elementName)->GetText() != nullptr)
		return this->getOrCreateElement(doc, parentNode, elementName)->GetText();
	return "";
}
