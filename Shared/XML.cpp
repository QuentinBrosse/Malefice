
#include "XML.h"

XML::XML(const char * szFileName)
{
	m_pRootNode = NULL;
	m_pNode = NULL;

	SetFileName(szFileName);

	Load();
}

XML::~XML(void)
{
	if (m_pNode)
	{
		delete m_pNode;

		m_pNode = NULL;
	}
}

bool XML::Load(void)
{
	if (!m_document.LoadFile(m_szFileName))
		return false;

	m_pRootNode = m_document.RootElement();

	m_pNode = new XMLNode(m_pRootNode, NULL);

	BuildChildren(m_pNode);

	return true;
}

bool XML::Save(void)
{
	return m_document.SaveFile();
}

void XML::BuildChildren(XMLNode * pNode)
{
	TiXmlElement * pXmlNode = pNode->GetNode();

	if (pXmlNode)
	{
		for (TiXmlNode * pCurNode = pXmlNode->FirstChildElement(); pCurNode; pCurNode = pCurNode->NextSibling())
		{
			if (pCurNode->Type() != TiXmlElement::ELEMENT)
				continue;

			XMLNode * pNewNode = new XMLNode(pCurNode->ToElement(), pNode);

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
			m_pRootNode = new TiXmlElement(szName);

			m_document.LinkEndChild(m_pRootNode);
		}

		m_pNode = new XMLNode(m_pRootNode, NULL);
	}

	m_pNode->SetName(szName);
	return m_pNode;
}

XMLNode::XMLNode(TiXmlElement * pNode, XMLNode * pParent) : m_pNode(pNode)
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
		TiXmlNode* pParent = m_pNode->Parent();

		if (pParent)
			pParent->RemoveChild(m_pNode);
		else
			delete m_pNode;
	}
}

void XMLNode::SetValue(const char * szValue)
{
	m_pNode->Clear();

	TiXmlText * pText = new TiXmlText(szValue);

	m_pNode->LinkEndChild(pText);
}

XMLNode * XMLNode::CreateSubNode(const char * szName)
{
	TiXmlElement * pNewNode = new TiXmlElement(szName);

	m_pNode->LinkEndChild(pNewNode);

	return new XMLNode(pNewNode, this);
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