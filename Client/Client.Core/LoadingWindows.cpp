#include <iostream>
#include "LoadingWindows.h"
#include "Audio.h"

LoadingWindows::LoadingWindows() :
	m_windows(nullptr), m_progressText(nullptr), m_outputList(nullptr), m_frameWindows(nullptr), m_systemd(CEGUI::System::getSingleton()), m_progressBar(nullptr)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("connectionToServer.layout");
	try
	{
		m_frameWindows = dynamic_cast<CEGUI::FrameWindow *>(m_windows->getChild(1));
		if (m_windows == nullptr)
			std::cout << "" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Failure while loading Frame windows:" << std::endl << std::endl;
		std::cout << e.what() << std::endl;
	}
	m_frameWindows->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LoadingWindows::onCloseButtonClicked, this));
	m_progressBar = dynamic_cast<CEGUI::ProgressBar *>(m_frameWindows->getChild(2));
	m_progressText = m_frameWindows->getChild(3);
	m_outputList = dynamic_cast<CEGUI::Listbox  *>(m_frameWindows->getChild(4));
}

void LoadingWindows::display()
{
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		std::cout << "Root Windows not found setting loading windows as root..." << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
}

void LoadingWindows::hide()
{
	try {
		m_systemd.getDefaultGUIContext().getRootWindow()->getChild(42)->getChild(1);
		m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(42);
	}
	catch (std::exception &e) {
		std::cout << "Root windows not found. hiding loading windows as Root Windows" << std::endl;
		m_systemd.getDefaultGUIContext().setRootWindow(0);
	}
}

bool LoadingWindows::onCloseButtonClicked(const CEGUI::EventArgs& e)
{
	Audio::getInstance().playGUISound(Audio::SoundType::GUI_BTN_PRESS);
	this->hide();
	return (true);
}

void LoadingWindows::setProgress(unsigned int progress)
{
	m_progressBar->setProgress(static_cast<float>(progress) / 100);
	m_progressText->setText(std::to_string(progress) + "%");
}

void LoadingWindows::listAddText(const std::string &txt)
{
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("default");
	item->setText(txt);
	m_outputList->addItem(item);
}
