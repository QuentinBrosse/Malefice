#pragma once

#include <string>
#include <map>
#include "Spell.h"
#include "Export.h"
#include "Singleton.h"
#include "SpellsConfiguration.h"

class MALEFICE_DLL_EXPORT SpellCreator: public Singleton<SpellCreator>
{
	friend class Singleton<SpellCreator>;

protected:
	SpellCreator();
	~SpellCreator()	= default;

public:
	ecs::Spell	create(const ecs::Spell::SpellType spellType);


private:
	std::map<ecs::Spell::SpellType, ecs::Spell>	m_spells;
	SpellsConfiguration*						m_configurator;
};
