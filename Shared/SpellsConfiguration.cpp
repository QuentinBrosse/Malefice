#include "SpellsConfiguration.h"

const std::string	SpellsConfiguration::SPELLS_FILENAME = "spells.xml";

bool	SpellsConfiguration::loadFromFile(const std::string& filepath)
{
	tinyxml2::XMLDocument	doc;
	tinyxml2::XMLElement*	SpellsElement;
	tinyxml2::XMLError		loadResult = doc.LoadFile(filepath.c_str());

	if (loadResult != tinyxml2::XMLError::XML_SUCCESS)
	{
		LOG_CRITICAL(GENERAL) << "Spells configuration file could not be read properly (error code: " << loadResult << ").";
		return false;
	}
	SpellsElement = doc.RootElement();
	if (SpellsElement == nullptr)
	{
		LOG_CRITICAL(GENERAL) << "Spells configuration file could not be read properly (error code: " << doc.ErrorID() << ").";
		return false;
	}
	for (tinyxml2::XMLElement* currentSpell = SpellsElement->FirstChildElement(); currentSpell != nullptr; currentSpell = currentSpell->NextSiblingElement())
	{
		int						id = 0;
		ecs::Spell::SpellType	type;
		std::string				name;
		int						cooldown;

		if (currentSpell->QueryIntAttribute("id", &id) != tinyxml2::XMLError::XML_NO_ERROR || id <= 0)
		{
			LOG_ERROR(GENERAL) << "Bad Spell ID \"" << id << "\", skipping element.";
			continue;
		}
		name = this->getOrCreateElementString(doc, *currentSpell, "name", "");
		type = this->parseSpellType(this->getOrCreateElementString(doc, *currentSpell, "type", ""));
		cooldown = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "cooldown", "-1"));
		if (name == "" || type == ecs::Spell::SPELL_COUNT || cooldown <= -1)
		{
			LOG_ERROR(GENERAL) << "Bad Spell element value, skipping element.";
			continue;
		}
		m_Spells.emplace(std::piecewise_construct, std::make_tuple(type), std::make_tuple(id, name, type, cooldown));
	}
	return true;
}

bool	SpellsConfiguration::saveToFile(const std::string& filepath)	const
{
	throw std::logic_error("SpellsConfiguration::saveToFile() not implemented");
}


const std::map<ecs::Spell::SpellType, ecs::Spell>	&SpellsConfiguration::getSpells()	const
{
	return m_Spells;
}


ecs::Spell::SpellType	SpellsConfiguration::parseSpellType(const std::string& SpellTypeStr)	const
{
	std::map<std::string, ecs::Spell::SpellType>	SpellTypes;
	auto											SpellType = SpellTypes.end();

	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("SNIPER_RIFLE", ecs::Spell::SpellType::SLOW));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("RAIL_GUN", ecs::Spell::SpellType::BLIND));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("SHOTGUN", ecs::Spell::SpellType::CONFUSION));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("MACHINE_GUN", ecs::Spell::SpellType::DEAF));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("REVOLVER", ecs::Spell::SpellType::NOTHING));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("DOUBLE_GUN", ecs::Spell::SpellType::PARANOIA));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("SABER", ecs::Spell::SpellType::PARKINSON));
	SpellType = SpellTypes.find(SpellTypeStr);
	if (SpellType != SpellTypes.end())
		return SpellType->second;
	else
		return ecs::Spell::SpellType::SPELL_COUNT;
}
