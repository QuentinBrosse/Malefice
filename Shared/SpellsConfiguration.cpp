#include "SpellsConfiguration.h"

const std::string	SpellsConfiguration::SPELLS_FILENAME = "Config\\spells.xml";

SpellsConfiguration::SpellsConfiguration()
{
	loadFromFile(SPELLS_FILENAME);
}

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
		int						duration;
		irr::core::vector3df	fpsMetricsPosition;
		irr::core::vector3df	fpsMetricsRotation;
		irr::core::vector3df	fpsMetricsScale;
		irr::core::vector3df	externalMetricsPosition;
		irr::core::vector3df	externalMetricsRotation;
		irr::core::vector3df	externalMetricsScale;
		std::string				meshName;

		if (currentSpell->QueryIntAttribute("id", &id) != tinyxml2::XMLError::XML_NO_ERROR || id <= 0)
		{
			LOG_ERROR(GENERAL) << "Bad Spell ID \"" << id << "\", skipping element.";
			continue;
		}
		name = this->getOrCreateElementString(doc, *currentSpell, "name", "");
		type = this->parseSpellType(this->getOrCreateElementString(doc, *currentSpell, "type", ""));
		cooldown = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "cooldown", "-1"));
		duration = std::stoi(this->getOrCreateElementString(doc, *currentSpell, "duration", "-1"));
		meshName = this->getOrCreateElementString(doc, *currentSpell, "meshName", "");

		if (name == "" || type == ecs::Spell::SPELL_COUNT || cooldown <= -1 || duration <= -1)
		{
			LOG_ERROR(GENERAL) << "Bad Spell element value, skipping element.";
			continue;
		}
		tinyxml2::XMLElement* fpsMetrics = this->getOrCreateElement(doc, *currentSpell, "FPSMetrics");
		if (fpsMetrics == nullptr)
		{
			LOG_ERROR(GENERAL) << "<FPSMetrics> not found, skipping element.";
			continue;
		}
		tinyxml2::XMLElement* position = this->getOrCreateElement(doc, *fpsMetrics, "position");
		if (position == nullptr)
		{
			LOG_ERROR(GENERAL) << "<position> not found inside <FPSMetrics>, skipping element.";
			continue;
		}
		else
		{
			irr::f32 x = std::stof(this->getOrCreateElementString(doc, *position, "x", ""));
			irr::f32 y = std::stof(this->getOrCreateElementString(doc, *position, "y", ""));
			irr::f32 z = std::stof(this->getOrCreateElementString(doc, *position, "z", ""));
			fpsMetricsPosition = irr::core::vector3df(x, y, z);
		}

		tinyxml2::XMLElement* rotation = this->getOrCreateElement(doc, *fpsMetrics, "rotation");
		if (rotation == nullptr)
		{
			LOG_ERROR(GENERAL) << "<rotation> not found inside <FPSMetrics>, skipping element.";
			continue;
		}
		else
		{
			irr::f32 x = std::stof(this->getOrCreateElementString(doc, *rotation, "x", ""));
			irr::f32 y = std::stof(this->getOrCreateElementString(doc, *rotation, "y", ""));
			irr::f32 z = std::stof(this->getOrCreateElementString(doc, *rotation, "z", ""));
			fpsMetricsRotation = irr::core::vector3df(x, y, z);
		}

		tinyxml2::XMLElement* scale = this->getOrCreateElement(doc, *fpsMetrics, "scale");
		if (scale == nullptr)
		{
			LOG_ERROR(GENERAL) << "<scale> not found inside <FPSMetrics>, skipping element.";
			continue;
		}
		else
		{
			irr::f32 x = std::stof(this->getOrCreateElementString(doc, *scale, "x", ""));
			irr::f32 y = std::stof(this->getOrCreateElementString(doc, *scale, "y", ""));
			irr::f32 z = std::stof(this->getOrCreateElementString(doc, *scale, "z", ""));
			fpsMetricsScale = irr::core::vector3df(x, y, z);
		}

		tinyxml2::XMLElement* externalMetrics = this->getOrCreateElement(doc, *currentSpell, "ExternalMetrics");
		if (externalMetrics == nullptr)
		{
			LOG_ERROR(GENERAL) << "<ExternalMetrics> not found, skipping element.";
			continue;
		}

		tinyxml2::XMLElement* positionExt = this->getOrCreateElement(doc, *externalMetrics, "position");
		if (positionExt == nullptr)
		{
			LOG_ERROR(GENERAL) << "<position> not found inside <ExternalMetrics>, skipping element.";
			continue;
		}
		else
		{
			irr::f32 x = std::stof(this->getOrCreateElementString(doc, *positionExt, "x", ""));
			irr::f32 y = std::stof(this->getOrCreateElementString(doc, *positionExt, "y", ""));
			irr::f32 z = std::stof(this->getOrCreateElementString(doc, *positionExt, "z", ""));
			externalMetricsPosition = irr::core::vector3df(x, y, z);
		}

		tinyxml2::XMLElement* rotationExt = this->getOrCreateElement(doc, *externalMetrics, "rotation");
		if (rotationExt == nullptr)
		{
			LOG_ERROR(GENERAL) << "<rotation> not found inside <ExternalMetrics>, skipping element.";
			continue;
		}
		else
		{
			irr::f32 x = std::stof(this->getOrCreateElementString(doc, *rotationExt, "x", ""));
			irr::f32 y = std::stof(this->getOrCreateElementString(doc, *rotationExt, "y", ""));
			irr::f32 z = std::stof(this->getOrCreateElementString(doc, *rotationExt, "z", ""));
			externalMetricsRotation = irr::core::vector3df(x, y, z);
		}

		tinyxml2::XMLElement* scaleExt = this->getOrCreateElement(doc, *externalMetrics, "scale");
		if (scaleExt == nullptr)
		{
			LOG_ERROR(GENERAL) << "<scale> not found inside <ExternalMetrics>, skipping element.";
			continue;
		}
		else
		{
			irr::f32 x = std::stof(this->getOrCreateElementString(doc, *scaleExt, "x", ""));
			irr::f32 y = std::stof(this->getOrCreateElementString(doc, *scaleExt, "y", ""));
			irr::f32 z = std::stof(this->getOrCreateElementString(doc, *scaleExt, "z", ""));
			externalMetricsScale = irr::core::vector3df(x, y, z);
		}
		
		m_Spells.emplace(std::piecewise_construct, std::make_tuple(type), std::make_tuple(id, name, type, cooldown, duration, ecs::Position(fpsMetricsPosition, fpsMetricsRotation, fpsMetricsScale), ecs::Position(externalMetricsPosition, externalMetricsRotation, externalMetricsScale), meshName));
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

	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("SLOW", ecs::Spell::SpellType::SLOW));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("BLIND", ecs::Spell::SpellType::BLIND));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("CONFUSION", ecs::Spell::SpellType::CONFUSION));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("DEAF", ecs::Spell::SpellType::DEAF));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("NOTHING", ecs::Spell::SpellType::NOTHING));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("PARANOIA", ecs::Spell::SpellType::PARANOIA));
	SpellTypes.insert(std::make_pair<std::string, ecs::Spell::SpellType>("PARKINSON", ecs::Spell::SpellType::PARKINSON));
	SpellType = SpellTypes.find(SpellTypeStr);
	if (SpellType != SpellTypes.end())
		return SpellType->second;
	else
		return ecs::Spell::SpellType::SPELL_COUNT;
}
