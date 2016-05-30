#pragma once
#include	<irrKlang.h>
#include	<string>
#include	<map>

#include	"Singleton.h"

class Audio : public Singleton<Audio>
{
	friend class Singleton<Audio>;

public:

	enum class SoundType : uint8_t
	{
		GUI_BTN_HOVER,
		GUI_BTN_PRESS,
		// GUI_BTN_RELEASE,
		COUNT
	};

	void	playGUISound(const SoundType);

protected:
	Audio();
	~Audio();

private:
	const std::string&								m_soundPath;
	irrklang::ISoundEngine*							m_engine;
	std::map<const SoundType, const std::string>	m_sounds;

};