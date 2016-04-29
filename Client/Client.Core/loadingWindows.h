#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <CEGUI/RendererModules/Irrlicht/Renderer.h>
#include <iostream>
#include <string>

class LoadingWindows
{
private:
	CEGUI::Window* m_windows;
	CEGUI::Window* m_progressText;
	CEGUI::Listbox* m_outputList;
	CEGUI::FrameWindow* m_frameWindows;
	CEGUI::System& m_systemd;
	irr::SKeyMap* m_keyMap;
	irr::IrrlichtDevice* m_device;
	irr::video::IVideoDriver* m_driver;
	irr::scene::ISceneManager* m_sceneManager;
	CEGUI::ProgressBar* m_progressBar;
public:
	LoadingWindows(irr::SKeyMap* keyMap, irr::scene::ISceneManager* sceneManager, irr::IrrlichtDevice* device);
	~LoadingWindows() = default;
	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
	void setProgress(unsigned int progress);
	void listAddText(const std::string& txt);
};