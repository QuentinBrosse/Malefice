#include "MasterList.h"
#include "GraphicUtil.h"

MasterList::MasterList(GraphicUtil &gu) : m_systemd(CEGUI::System::getSingleton()), m_graphicUtils(gu)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("masterList.layout");
	m_windows->setName("MasterList");
	m_manualConnect = dynamic_cast<CEGUI::PushButton *>(m_windows->getChild(1));
	m_autoConnect = dynamic_cast<CEGUI::PushButton *>(m_windows->getChild(2));
	m_serverList = dynamic_cast<CEGUI::Listbox *>(m_windows->getChild(33));
	if (m_serverList == nullptr)
		LOG_DEBUG(GENERAL) << "Cannot cast !";
	m_frameWindow = dynamic_cast<CEGUI::FrameWindow *>(m_windows);
	m_frameWindow->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MasterList::onCloseButtonClicked, this));
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MasterList::onManualConnectButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MasterList::onAutoConnectButtonClicked, this));

	m_frameWindow->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MasterList::onCloseButtonEnterArea, this));
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MasterList::onManualConnectButtonEnterArea, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea, CEGUI::Event::Subscriber(&MasterList::onAutoConnectButtonEnterArea, this));

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

void MasterList::addServer(const std::string& ip, const std::string& port, bool hasPassword, int players)
{
	Server *info = new Server();
	info->setHasPassword(hasPassword);
	info->setIp(ip);
	info->setPort(port);
	CEGUI::ListboxItem* item = new CEGUI::ListboxTextItem("ok");
	item->setText("[colour='FF000000']IP: " + ip + "   Port: " + port + "    Players: " + (players < 0 ? std::string("unknown") : std::to_string(players)) + (hasPassword ? "   (has password)" : "   (no password)"));
	item->setUserData(info);
	item->setSelectionBrushImage("WindowsLook/TitlebarBottom");
	item->setSelected(false);
	m_serverList->addItem(item);
}

void MasterList::resetList()
{
	m_serverList->resetList();
}

bool MasterList::onManualConnectButtonClicked(const CEGUI::EventArgs& e)
{
	this->hide();
	m_graphicUtils.getConnectWindow()->display();
	return (true);
}

bool MasterList::onAutoConnectButtonClicked(const CEGUI::EventArgs& e)
{
	CEGUI::ListboxItem* item = m_serverList->getFirstSelectedItem();
	if (item != nullptr && item->getUserData() != nullptr)
	{
		Server *info = reinterpret_cast<Server *>(item->getUserData());
		m_graphicUtils.getConnectWindow()->setIp(info->getIp());
		m_graphicUtils.getConnectWindow()->setPort(info->getPort());
	}
	this->hide();
	m_graphicUtils.getConnectWindow()->display();
	return (true);
}

bool MasterList::onCloseButtonClicked(const CEGUI::EventArgs& e)
{
	this->hide();
	return (true);
}

void MasterList::Server::setIp(const std::string &ip)
{
	this->m_ip = ip;
}

void MasterList::Server::setPort(const std::string &port)
{
	this->m_port = port;
}

void MasterList::Server::setHasPassword(bool password)
{
	this->m_password = password;
}

const std::string& MasterList::Server::getIp() const
{
	return m_ip;
}

const std::string& MasterList::Server::getPort() const
{
	return m_port;
}

bool MasterList::Server::hasPassword() const
{
	return m_password;
}

bool MasterList::onCloseButtonEnterArea(const CEGUI::EventArgs& e)
{
	return true;
}

bool MasterList::onManualConnectButtonEnterArea(const CEGUI::EventArgs& e)
{
	return true;
}

bool MasterList::onAutoConnectButtonEnterArea(const CEGUI::EventArgs& e)
{
	return true;
}