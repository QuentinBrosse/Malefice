#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <vector>
#include <string>
#include <iostream>

class MasterList
{
public:
	MasterList();
	~MasterList() = default;
	void display();
	void hide();
	void addServer(const std::string &txt);
	void resetList();
private:
	CEGUI::System&		m_systemd;
	CEGUI::Window*		m_windows;
	CEGUI::PushButton*	m_manualConnect;
	CEGUI::PushButton*	m_autoConnect;
	CEGUI::Listbox*		m_serverList;
};