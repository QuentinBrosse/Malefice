#pragma once

#include <string>
#include <map>
#include "Spell.h"

class SpellCreator
{
public:
	SpellCreator(const std::string& XMLFilename);
	~SpellCreator()	= default;

	ecs::Spell	create(const ecs::Spell::SpellType spellType);
	void		loadSpells();


private:
	std::map<ecs::Spell::SpellType, ecs::Spell>	m_spells;
	const std::string							XML_FILENAME;
};
