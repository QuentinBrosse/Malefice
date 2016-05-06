#include <exception>
#include "SpellsConfiguration.h"
#include "Logger.h"

bool	SpellsConfiguration::loadFromFile(const std::string& filepath)
{
	tinyxml2::XMLDocument	doc;
	tinyxml2::XMLElement*	SpellsElement;
	tinyxml2::XMLError		loadResult = doc.LoadFile(filepath.c_str());

	if (loadResult != tinyxml2::XMLError::XML_SUCCESS)
	{
		LOG_CRITICAL << "Spells configuration file could not be read properly (error code: " << loadResult << ", error message: " << doc.GetErrorStr2() << ").";
		return false;
	}
	SpellsElement = doc.RootElement();
	if (SpellsElement == nullptr)
	{
		LOG_CRITICAL << "Spells configuration file could not be read properly (error code: " << doc.ErrorID() << ", error message: " << doc.GetErrorStr2() << ").";
		return false;
	}
	for (tinyxml2::XMLElement* currentSpell = SpellsElement->FirstChildElement(); currentSpell != nullptr; currentSpell = currentSpell->NextSiblingElement())
	{
		int						id = 0;
		ecs::Spell::SpellType	type;
		std::string				name;
		int						maxAmmunition;
		int						maxAmmunitionExplosive;
		int						maxAmmunitionLoader;
		int						maxAmmunitionExplosiveLoader;
		int						damage;
		int						damageExplosive;
		std::string				handToHandStr;
		bool					handToHand;

		if (currentSpell->QueryIntAttribute("id", &id) != tinyxml2::XMLError::XML_NO_ERROR || id <= 0)
		{
			LOG_ERROR << "Bad Spell ID \"" << id << "\", skipping element.";
			continue;
		}
		name = this->getOrCreateElementString(doc, *currentSpell, "name", "");
		type = this->parseSpellType(this->getOrCreateElementString(doc, *currentSpell, "type", ""));
		maxAmmunition = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "maxAmmunition", "-1"));
		maxAmmunitionExplosive = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "maxAmmunitionExplosive", "-1"));
		maxAmmunitionLoader = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "maxAmmunitionLoader", "-1"));
		maxAmmunitionExplosiveLoader = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "maxAmmunitionExplosiveLoader", "-1"));
		damage = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "damage", "-1"));
		damageExplosive = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "damageExplosive", "-1"));
		handToHandStr = this->getOrCreateElementString(doc, *currentSpell, "handToHand", "");
		if (handToHandStr != "TRUE" && handToHandStr != "FALSE")
		{
			LOG_ERROR << "Bad Spell \"handToHand\" value \"" << handToHandStr << "\", skipping element.";
			continue;
		}
		else
		{
			handToHand = (handToHandStr == "TRUE" ? true : false);
		}
		if (name == "" || type == ecs::Spell::Spell_COUNT || maxAmmunition <= -1 || maxAmmunitionExplosive <= -1 || maxAmmunitionLoader <= -1 || maxAmmunitionExplosiveLoader <= -1 || damage <= -1 || damageExplosive <= -1)
		{
			LOG_ERROR << "Bad Spell element value, skipping element.";
			continue;
		}
		m_Spells.emplace(std::piecewise_construct, std::make_tuple(type), std::make_tuple(id, name, maxAmmunition, maxAmmunitionExplosive, damage, damageExplosive, maxAmmunitionLoader, maxAmmunitionExplosiveLoader, type, handToHand)); // TODO: add maxAmmunitionLoader and maxAmmunitionExplosiveLoader
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

	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("SNIPER_RIFLE", ecs::Spell::SpellType::SNIPER_RIFLE));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("RAIL_GUN", ecs::Spell::SpellType::RAIL_GUN));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("SHOTGUN", ecs::Spell::SpellType::SHOTGUN));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("MACHINE_GUN", ecs::Spell::SpellType::MACHINE_GUN));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("REVOLVER", ecs::Spell::SpellType::REVOLVER));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("DOUBLE_GUN", ecs::Spell::SpellType::DOUBLE_GUN));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("SABER", ecs::Spell::SpellType::SABER));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("CHAIN_SAW", ecs::Spell::SpellType::CHAIN_SAW));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("KNIFE", ecs::Spell::SpellType::KNIFE));
	SpellType = SpellTypes.find(SpellTypeStr);
	if (SpellType != SpellTypes.end())
		return SpellType->second;
	else
		return ecs::Spell::SpellType::Spell_COUNT;
}
