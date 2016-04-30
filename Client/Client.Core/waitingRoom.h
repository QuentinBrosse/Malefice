#pragma once

#include <ctime>
#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>

class WaitingRoom
{
public:
	WaitingRoom(irr::SKeyMap* keyMap, irr::scene::ISceneManager* sceneManager, irr::IrrlichtDevice* device);
	~WaitingRoom()	= default;

	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
	void refreshTime();
	void addRightTeamMember(const std::string &);
	void addLeftTeamMember(const std::string& txt);


private:
	CEGUI::Window*				m_windows;
	irr::SKeyMap*				m_keyMap;
	irr::IrrlichtDevice*		m_device;
	irr::video::IVideoDriver*	m_driver;
	irr::scene::ISceneManager*	m_sceneManager;
	CEGUI::System&				m_systemd;
	CEGUI::FrameWindow*			m_frameWindows;
	std::time_t					m_timestamp;
	bool						m_stopTimer = false;
	CEGUI::Window*				m_timerText;
	CEGUI::Listbox*				m_rightTeam;
	CEGUI::Listbox*				m_leftTeam;
};
