#include "YourDead.h"

YourDead::YourDead() : m_systemd(CEGUI::System::getSingleton()), m_isDisplayed(false), m_time(0), m_delay(3000)
{
	m_windows = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("dead.layout");
	m_windows->setName("Your are dead");
	m_isDisplayed = false;
}

void YourDead::hide()
{
	m_isDisplayed = false;
	try {
		if (m_systemd.getDefaultGUIContext().getRootWindow()->getChild(m_windows->getID()))
		{
			m_systemd.getDefaultGUIContext().getRootWindow()->removeChild(m_windows->getID());
		}
	}
	catch (std::exception &e)
	{

	}
}

void YourDead::display()
{
	m_isDisplayed = true;
	m_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	if (m_systemd.getDefaultGUIContext().getRootWindow() == nullptr)
	{
		m_systemd.getDefaultGUIContext().setRootWindow(m_windows);
	}
	else
	{
		m_systemd.getDefaultGUIContext().getRootWindow()->addChild(m_windows);
	}
}

void YourDead::setPseudo(const std::string &txt)
{
	m_windows->getChild(3310)->setText(txt.c_str());
}

void YourDead::refresh()
{
	std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	if ((time - m_time) >= m_delay && m_isDisplayed)
	{
		this->hide();
		m_isDisplayed = false;
		m_time = time;
	}
}