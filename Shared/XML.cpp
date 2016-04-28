
#include "XML.h"

XML::XML(const char * szFileName)
{
	m_pRootNode = nullptr;
	m_pNode = nullptr;

	SetFileName(szFileName);

	Load();
}

XML::~XML(void)
{
	if (m_pNode)
	{
		delete m_pNode;
		m_pNode = nullptr;
	}
}

bool XML::Load(void)
{
	if (!m_document.LoadFile(m_szFileName))
		return false;

	m_pRootNode = m_document.RootElement();

	m_pNode = new XMLNode(&m_document, m_pRootNode, NULL);

	BuildChildren(m_pNode);

	return true;
}

bool XML::Save(void)
{
	return m_document.SaveFile(m_szFileName);
}

void XML::BuildChildren(XMLNode * pNode)
{
	tinyxml2::XMLElement* pXmlNode = pNode->GetNode();

	if (pXmlNode)
	{
		for (tinyxml2::XMLNode* pCurNode = pXmlNode->FirstChildElement(); pCurNode; pCurNode = pCurNode->NextSibling())
		{
			if (pCurNode->ToElement() == nullptr)
				continue;

			XMLNode * pNewNode = new XMLNode(&m_document, pCurNode->ToElement(), pNode);

			BuildChildren(pNewNode);
		}
	}
}

XMLNode * XML::CreateRootNode(const char * szName)
{
	if (!m_pNode)
	{
		if (!m_pRootNode)
		{
			m_pRootNode = m_document.NewElement(szName);
			m_document.LinkEndChild(m_pRootNode);
		}

		m_pNode = new XMLNode(&m_document, m_pRootNode, NULL);
	}

	m_pNode->SetName(szName);
	return m_pNode;
}

XMLNode::XMLNode(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement * pNode, XMLNode * pParent) :
	m_doc(doc),
	m_pNode(pNode)
{
	m_pParent = pParent;

	if (pParent)
		pParent->AddChild(this);
}

XMLNode::~XMLNode(void)
{
	// Delete all children
	//for( std::list< XMLNode* >::iterator iter = m_Children.begin(); iter != m_Children.end(); iter++ ) {
	//	CLogFile::Printf( "Deleting node memory 0x%p (%s)...", *iter, (*iter)->GetValue() );
	//	delete *iter;  // todo: MAKE SURE THIS DOESN'T LEAK MEMORY!
	//	CLogFile::Printf( "Done!" );
	//}

	m_Children.clear();

	if (m_pParent)
		m_pParent->RemoveChild(this);

	if (m_pNode)
	{
		tinyxml2::XMLNode* pParent = m_pNode->Parent();

		if (pParent)
			pParent->DeleteChild(m_pNode);
	}
}

void XMLNode::SetValue(const char* szValue)
{
	tinyxml2::XMLText * pText = m_doc->NewText(szValue);

	m_pNode->LinkEndChild(pText);
}

XMLNode * XMLNode::CreateSubNode(const char * szName)
{
	tinyxml2::XMLElement* pNewNode = m_doc->NewElement(szName);

	m_pNode->LinkEndChild(pNewNode);

	return new XMLNode(m_doc, pNewNode, this);
}

XMLNode * XMLNode::FindNode(const char * szName)
{
	for (std::list< XMLNode* >::iterator iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		if (!strcmp((*iter)->GetName(), szName))
			return *iter;
	}

	return NULL;
}

XMLNode * XMLNode::GetNode(unsigned int uiIndex)
{
	unsigned int uiCurrentIndex = 0;

	for (std::list< XMLNode* >::iterator iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		if (uiCurrentIndex == uiIndex)
			return *iter;

		uiCurrentIndex++;
	}

	return NULL;
}
