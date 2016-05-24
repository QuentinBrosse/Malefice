#include "MasterList.h"
#include "GraphicUtil.h"

MasterList::MasterList(GraphicUtil &gu) : m_systemd(CEGUI::System::getSingleton()), m_graphicUtils(gu)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("masterList.layout");
	m_manualConnect = dynamic_cast<CEGUI::PushButton *>(m_windows->getChild(1));
	m_autoConnect = dynamic_cast<CEGUI::PushButton *>(m_windows->getChild(2));
	m_serverList = dynamic_cast<CEGUI::Listbox *>(m_windows->getChild(33));
	if (m_serverList == nullptr)
		LOG_DEBUG(GENERAL) << "Cannot cast !";
	m_frameWindow = dynamic_cast<CEGUI::FrameWindow *>(m_windows);
	m_frameWindow->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MasterList::onCloseButtonClicked, this));
	m_windows->getChild(1)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MasterList::onManualConnectButtonClicked, this));
	m_windows->getChild(2)->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MasterList::onAutoConnectButtonClicked, this));
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
	CEGUI::ListboxItem* item = new CEGUI::ListboxTextItem("ok");
	item->setText(txt);
	item->setUserData(0);
	item->setSelectionBrushImage("WindowsLook/TitlebarBottom");
	item->setSelected(false);
	m_serverList->addItem(item);
}

void MasterList::resetList()
{
	m_serverList->resetList();
}

bool MasterList::onManualConnectButtonClicked()
{
	this->hide();
	m_graphicUtils.getConnectWindow()->display();
	return (true);
}

bool MasterList::onAutoConnectButtonClicked()
{
	CEGUI::ListboxItem* item = m_serverList->getFirstSelectedItem();
	this->hide();
	m_graphicUtils.getConnectWindow()->display();
	return (true);
}

bool MasterList::onCloseButtonClicked()
{
	this->hide();
	return (true);
}
#include "ProjectGlobals.h"

#include "MasterList.h"

#include <iostream>
MasterList::MasterList(): Singleton<MasterList>(),
	m_lastUpdateTime(0)
{
	m_tcp = RakNet::OP_NEW<RakNet::TCPInterface>(__FILE__, __LINE__);
	m_tcp->Start(0, 64);
}

MasterList::~MasterList()
{
	if (m_tcp) {
		if (m_tcp->WasStarted())
			m_tcp->Stop();
		delete(m_tcp);
	}
}

std::vector<std::string>	MasterList::fetch()
{
	RakNet::RakString			post;
	RakNet::Packet*				packet;
	std::vector<std::string>	retn;

	if ((utility::TimeUtility::getMsTime() - m_lastUpdateTime) < 3000)
		return retn;

	if (m_tcp->Connect(ProjectGlobals::MASTERLIST_URL.c_str(), 80, true) == RakNet::UNASSIGNED_SYSTEM_ADDRESS)
		return retn;

	RakSleep(100);

	post = RakNet::RakString::FormatForGET(std::string(ProjectGlobals::MASTERLIST_URL).append("/api/v1/server?ordered=true").c_str(), "User-Agent: Malefice/1.0");

	m_tcp->Send(post.C_String(), post.GetLength(), m_tcp->HasCompletedConnectionAttempt(), false);

	RakSleep(1000);

	packet = m_tcp->Receive();
	if (!packet)
		return retn;

	std::cout << packet->data;

	m_lastUpdateTime = utility::TimeUtility::getMsTime();
	m_tcp->DeallocatePacket(packet);

	return retn;
}