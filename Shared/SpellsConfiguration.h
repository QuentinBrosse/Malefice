#pragma once

#include <string>
#include <map>
#include <tinyxml2.h>
#include "Logger.h"
#include <exception>

#include "AConfiguration.h"
#include "Spell.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT SpellsConfiguration : public AConfiguration, public Singleton<SpellsConfiguration>
{
	friend class Singleton<SpellsConfiguration>;

protected:
	SpellsConfiguration() = default;
	virtual ~SpellsConfiguration() = default;

public:
	virtual bool	loadFromFile(const std::string& filepath);
	virtual bool	saveToFile(const std::string& filepath)	const;

	const std::map<ecs::Spell::SpellType, ecs::Spell>	&getSpells()	const;


private:
	static const std::string	SPELLS_FILENAME;

	ecs::Spell::SpellType	parseSpellType(const std::string& SpellTypeStr)	const;

	std::map<ecs::Spell::SpellType, ecs::Spell>	m_Spells;
};
