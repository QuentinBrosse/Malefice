#include "Audio.h"

Audio::Audio() :
	m_soundPath("Media/Sounds/")
{
	m_sounds.insert(std::make_pair(SoundType::GUI_BTN_HOVER, m_soundPath + "gui_hover.wav"));
	m_sounds.insert(std::make_pair(SoundType::GUI_BTN_PRESS, m_soundPath + "gui_press.wav"));

	m_engine = irrklang::createIrrKlangDevice();
}

Audio::~Audio()
{
	m_engine->drop();
}

void	Audio::playGUISound(const Audio::SoundType soundType)
{
	m_engine->play2D(m_sounds[soundType].c_str());
}