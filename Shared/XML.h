#pragma once

#include "StdInc.h"

#include "../Libraries/ticpp/tinyxml.h"
#include "../Libraries/ticpp/ticpprc.h"
#include "../Libraries/ticpp/ticpp.h"


class XMLNode;
class XML
{

private:

	TiXmlDocument				m_document;
	TiXmlElement				* m_pRootNode;
	XMLNode						* m_pNode;

	const char					* m_szFileName;

	void						BuildChildren(XMLNode * pNode);

public:

	XML(const char * szFileName);
	~XML(void);

	void						SetFileName(const char * szFileName) { m_szFileName = szFileName; }
	const char					* GetFileName(void) { return m_szFileName; }

	bool						Load(void);
	bool						Save(void);

	XMLNode						* CreateRootNode(const char * szName);
	XMLNode						* GetRootNode(void) { return m_pNode; }

	TiXmlDocument				GetXMLDocument(void) { return m_document; }
	TiXmlElement				* GetXMLRootNode(void) { return m_pRootNode; }

};

class XMLNode
{

private:

	TiXmlElement				* m_pNode;
	XMLNode						* m_pParent;

	std::list< XMLNode* >		m_Children;

public:

	XMLNode(TiXmlElement * pNode, XMLNode * pParent = NULL);
	~XMLNode(void);

	void						SetName(const char * szName) { m_pNode->SetValue(szName); }
	const char					* GetName(void) { return m_pNode->Value(); }

	void						SetValue(const char * szValue);
	const char					* GetValue(void) { return m_pNode->GetText(); }

	XMLNode						* CreateSubNode(const char * szName);
	XMLNode						* FindNode(const char * szName);
	XMLNode						* GetNode(unsigned int uiIndex);

	void						SetAttribute(const char * szName, const char * szValue) { m_pNode->SetAttribute(szName, szValue); }
	const char					* GetAttribute(const char * szName) { return m_pNode->Attribute(szName); }

	void						AddChild(XMLNode * pNode) { m_Children.push_back(pNode); }
	void						RemoveChild(XMLNode * pNode) { if (!m_Children.empty()) { m_Children.remove(pNode); } }
	unsigned int				GetChildCount(void) { return m_Children.size(); }
	std::list< XMLNode* >		GetChildren(void) { return m_Children; }

	TiXmlElement				* GetNode(void) { return m_pNode; }
	XMLNode						* GetParent(void) { return m_pParent; }

};