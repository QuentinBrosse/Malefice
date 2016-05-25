#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <vector>
#include <string>
#include <iostream>

class GraphicUtil;

class MasterList
{
public:
	MasterList(GraphicUtil &gu);
	~MasterList() = default;
	void display();
	void hide();
	void addServer(const std::string& ip, const std::string& port, bool hasPassword = false, int players = -1);
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