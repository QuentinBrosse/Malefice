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
	bool onCloseButtonClicked();
	bool onCloseButtonEnterArea();
	bool onValidateButtonEnterArea();
	bool onCancellButtonEnterArea();
private:
	CEGUI::System& m_systemd;
	CEGUI::Window* m_windows;
	CEGUI::FrameWindow* m_frameWindows;
	GraphicUtil& m_utilities;
};