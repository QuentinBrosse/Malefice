#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <vector>
#include <string>
#include <iostream>
#include	<vector>

#include	<TCPInterface.h>
#include	<RakSleep.h>
#include	<RakString.h>

#include	"Singleton.h"

#include	"TimeUtility.h"

class MasterList : public Singleton<MasterList>
{
	friend class Singleton<MasterList>;

class MasterList
{
public:
	MasterList(GraphicUtil &gu);
	~MasterList() = default;
	void display();
	void hide();
	void addServer(const std::string &txt);
	void resetList();
	bool onManualConnectButtonClicked();
	bool onAutoConnectButtonClicked();
	bool onCloseButtonClicked();

private:
	CEGUI::System&		m_systemd;
	GraphicUtil&		m_graphicUtils;
	CEGUI::FrameWindow*	m_frameWindow;
	CEGUI::Window*		m_windows;
	CEGUI::PushButton*	m_manualConnect;
	CEGUI::PushButton*	m_autoConnect;
	CEGUI::Listbox*		m_serverList;
	MasterList();
	~MasterList();

	std::vector<std::string> fetch();

private:
	RakNet::TCPInterface*	m_tcp;
	long long				m_lastUpdateTime;
};