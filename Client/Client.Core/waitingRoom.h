#pragma once

#include <ctime>
#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>

class WaitingRoom
{
public:
	WaitingRoom();
	~WaitingRoom()	= default;

	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
	void refreshTime();
	void addRightTeamMember(const std::string& name);
	void addLeftTeamMember(const std::string& name);

private:
	CEGUI::Window*				m_windows;
	CEGUI::System&				m_systemd = CEGUI::System::getSingleton();
	CEGUI::FrameWindow*			m_frameWindows;
	std::time_t					m_timestamp;
	bool						m_stopTimer = false;
	CEGUI::Window*				m_timerText;
	CEGUI::Listbox*				m_rightTeam;
	CEGUI::Listbox*				m_leftTeam;
};
