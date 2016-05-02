#pragma once

#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>

class LoadingWindows
{
public:
	LoadingWindows();
	~LoadingWindows()	= default;

	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
	void setProgress(unsigned int progress);
	void listAddText(const std::string& txt);


private:
	CEGUI::Window* m_windows;
	CEGUI::Window* m_progressText;
	CEGUI::Listbox* m_outputList;
	CEGUI::FrameWindow* m_frameWindows;
	CEGUI::System& m_systemd = CEGUI::System::getSingleton();
	CEGUI::ProgressBar* m_progressBar;
};
