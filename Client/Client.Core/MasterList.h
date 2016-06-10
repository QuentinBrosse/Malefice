#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <vector>
#include <string>
#include <iostream>

class MasterListNetwork;
#include "MasterListNetwork.h"

class GraphicUtil;

class MasterList
{
public:
	MasterList(GraphicUtil &gu);
	~MasterList() = default;
	static void fetchNetwork(const std::vector<std::string>& servers, MasterList& master);
	void display();
	void hide();
	void addServer(const std::string& ip, const std::string& port, bool hasPassword = false, int players = -1);
	void resetList();
	bool onManualConnectButtonClicked(const CEGUI::EventArgs& e);
	bool onAutoConnectButtonClicked(const CEGUI::EventArgs& e);
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);

	bool onCloseButtonEnterArea(const CEGUI::EventArgs& e);
	bool onManualConnectButtonEnterArea(const CEGUI::EventArgs& e);
	bool onAutoConnectButtonEnterArea(const CEGUI::EventArgs& e);

private:
	CEGUI::System&		m_systemd;
	GraphicUtil&		m_graphicUtils;
	CEGUI::FrameWindow*	m_frameWindow;
	CEGUI::Window*		m_windows;
	CEGUI::PushButton*	m_manualConnect;
	CEGUI::PushButton*	m_autoConnect;
	CEGUI::Listbox*		m_serverList;
	MasterListNetwork*	m_masterListNework;
	class Server
	{
	public:
		Server() = default;
		~Server() = default;
		void setIp(const std::string &);
		void setPort(const std::string &);
		void setHasPassword(bool);
		const std::string& getIp() const;
		const std::string& getPort() const;
		bool hasPassword() const;
	private:
		std::string m_ip;
		std::string m_port;
		bool m_password;
	};
};