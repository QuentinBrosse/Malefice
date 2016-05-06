#pragma once

#pragma once

#include <string>
#include <map>
#include <tinyxml2.h>
#include "AConfiguration.h"
#include "Spell.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT SpellsConfiguration : public AConfiguration
{
public:
	static const std::string	SPELLS_FILENAME;

	SpellsConfiguration() = default;
	virtual ~SpellsConfiguration() = default;

	virtual bool	loadFromFile(const std::string& filepath);
	virtual bool	saveToFile(const std::string& filepath)	const;


	const std::map<ecs::Spell::SpellType, ecs::Spell>	&getSpells()	const;


private:
	ecs::Spell::SpellType	parseSpellType(const std::string& SpellTypeStr)	const;

	std::map<ecs::Spell::SpellType, ecs::Spell>	m_Spells;
};
