#include "waitingRoom.h"

#ifdef _MSC_VER
	#pragma warning(disable:4996)
#endif

WaitingRoom::WaitingRoom(irr::SKeyMap *keyMap, irr::scene::ISceneManager *sceneManager, irr::IrrlichtDevice *device) : m_systemd(CEGUI::System::getSingleton()), m_keyMap(keyMap), m_sceneManager(sceneManager), m_device(device)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("WaitingRoom.layout");
	try
	{
		m_frameWindows = dynamic_cast<CEGUI::FrameWindow *>(m_windows);
	}
	catch (std::exception &e)
	{
		std::cout << "Failure while loading Frame windows with id 100 (decimal)." << std::endl << std::endl;
		std::cout << e.what() << std::endl;
	}
	m_frameWindows->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&WaitingRoom::onCloseButtonClicked, this));
	m_timerText = m_frameWindows->getChild(101);
	m_rightTeam = dynamic_cast<CEGUI::Listbox *>(m_frameWindows->getChild(103));
	m_leftTeam = dynamic_cast<CEGUI::Listbox *>(m_frameWindows->getChild(102));
}

void WaitingRoom::display()
{
	std::cout << "Timer started" << std::endl;
	m_stopTimer = false;
	m_timestamp = std::time(nullptr);
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		std::cout << "Root Windows not found setting loading windows as root..." << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
}

void WaitingRoom::hide()
{
	std::cout << "Timer stoped" << std::endl;
	m_stopTimer = true;
	try {
		m_systemd.getDefaultGUIContext().getRootWindow()->getChild(100);
		m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(100);
	}
	catch (std::exception &e) {
		std::cout << "Root windows not found. hiding loading windows as Root Windows" << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(0);
	}
}

bool WaitingRoom::onCloseButtonClicked(const CEGUI::EventArgs& e)
{
	this->hide();
	return (true);
}

void WaitingRoom::refreshTime()
{
	if (!m_stopTimer)
	{
		std::time_t result = std::time(nullptr);
		m_timerText->setText("Temps �coul�: " + std::to_string((result - m_timestamp) / 60) + "m et " + std::to_string((result - m_timestamp) % 60) + "s");
	}
}

void WaitingRoom::addRightTeamMember(const std::string &txt)
{
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("default");
	item->setText(txt);
	m_rightTeam->addItem(item);
}

void WaitingRoom::addLeftTeamMember(const std::string &txt)
{
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("default");
	item->setText(txt);
	m_leftTeam->addItem(item);
}