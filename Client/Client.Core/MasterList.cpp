#include "MasterList.h"

MasterList::MasterList() : m_systemd(CEGUI::System::getSingleton())
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("masterList.layout");
	m_manualConnect = dynamic_cast<CEGUI::PushButton *>(m_windows->getChild(1));
	m_autoConnect = dynamic_cast<CEGUI::PushButton *>(m_windows->getChild(2));
	m_serverList = dynamic_cast<CEGUI::Listbox *>(m_windows->getChild(10));
}

void MasterList::display()
{
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		std::cout << "Root Windows not found setting loading windows as root..." << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
}

void MasterList::hide()
{
	try {
		m_systemd.getDefaultGUIContext().getRootWindow()->getChild(1234);
		m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(1234);
	}
	catch (std::exception &e) {
		std::cout << "Root windows not found. hiding loading windows as Root Windows" << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(0);
	}
}

void MasterList::addServer(const std::string &txt)
{
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("default");
	item->setText(txt);
	m_serverList->addItem(item);
}

void MasterList::resetList()
{
	m_serverList->resetList();
}