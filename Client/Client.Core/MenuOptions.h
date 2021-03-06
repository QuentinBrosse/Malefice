#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <iostream>

class GraphicUtil;

class MenuOptions
{
public:
	MenuOptions(GraphicUtil &gu);
	~MenuOptions() = default;

	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
	bool onCloseButtonEnterArea(const CEGUI::EventArgs& e);
	bool onValidateButtonEnterArea(const CEGUI::EventArgs& e);
	bool onCancellButtonEnterArea(const CEGUI::EventArgs& e);
private:
	CEGUI::System& m_systemd;
	CEGUI::Window* m_windows;
	CEGUI::FrameWindow* m_frameWindows;
	GraphicUtil& m_utilities;
};