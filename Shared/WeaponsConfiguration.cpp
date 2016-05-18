#include <string>
#include <exception>
#include "WeaponsConfiguration.h"
#include "Logger.h"

const std::string	WeaponsConfiguration::WEAPONS_FILENAME = "Config\\weapons.xml";

WeaponsConfiguration::WeaponsConfiguration()
{
	loadFromFile(WEAPONS_FILENAME);
}

bool	WeaponsConfiguration::loadFromFile(const std::string& filepath)
{
	tinyxml2::XMLDocument	doc;
	tinyxml2::XMLElement*	weaponsElement;
	tinyxml2::XMLError		loadResult = doc.LoadFile(filepath.c_str());

	if (loadResult != tinyxml2::XMLError::XML_SUCCESS)
	{
		char *toto = (char *)calloc(500, 1);
		GetCurrentDirectoryA(500, toto);

		LOG_CRITICAL(GENERAL) << toto << "Weapons configuration file could not be read properly (error code: " << loadResult << ").";
		return false;
	}
	weaponsElement = doc.RootElement();
	if (weaponsElement == nullptr)
	{
		LOG_CRITICAL(GENERAL) << "Weapons configuration file could not be read properly (error code: " << doc.ErrorID() << ").";
		return false;
	}

	for (tinyxml2::XMLElement* currentWeapon = weaponsElement->FirstChildElement(); currentWeapon != nullptr; currentWeapon = currentWeapon->NextSiblingElement())
	{
		bool					sight = false;
		float					distance;
		float					precision;
		float					fireRate = 0.0;
		int						damageExplosive;
		int						id = 0;
		unsigned int			ammunition = 0;
		unsigned int			ammoPerShot = 0;
		unsigned int			damage = 0;
		unsigned int			reloadTime = 0;
		unsigned int			defaultAmunitions = 0;
		ecs::Weapon::WeaponType	type;
		std::string				name;
		std::string				meshName;
		std::string				distanceStr;
		std::string				reloadTimeStr;
		std::string				damageStr;
		std::string				fireRateStr;
		std::string				ammoPerShotStr;
		std::string				precisionStr;
		std::string				ammunitionStr;
		std::string				defaultAmunitionsStr;
		irr::core::vector3df	fpsMetricsPosition;
		irr::core::vector3df	fpsMetricsRotation;
		irr::core::vector3df	fpsMetricsScale;
		irr::core::vector3df	externalMetricsPosition;
		irr::core::vector3df	externalMetricsRotation;
		irr::core::vector3df	externalMetricsScale;

		if (currentWeapon->QueryIntAttribute("id", &id) != tinyxml2::XMLError::XML_NO_ERROR || id <= 0)
		{
			LOG_ERROR(GENERAL) << "Bad weapon ID \"" << id << "\", skipping element.";
			continue;
		}
		name = this->getOrCreateElementString(doc, *currentWeapon, "name", "");
		meshName = this->getOrCreateElementString(doc, *currentWeapon, "meshName", "");
		type = this->parseWeaponType(this->getOrCreateElementString(doc, *currentWeapon, "type", ""));
		damage = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "damage", "-1"));
		damageExplosive = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "damageExplosive", "-1"));
		distanceStr = this->getOrCreateElementString(doc, *currentWeapon, "distance", "");
		distance = std::stof(distanceStr);
		tinyxml2::XMLElement* sightElem = this->getOrCreateElement(doc, *currentWeapon, "distance");
		if (sightElem != nullptr)
			sightElem->QueryBoolAttribute("sight", &sight);
		else
			sight = false;
		precisionStr = this->getOrCreateElementString(doc, *currentWeapon, "precision", "");
		precision = stof(precisionStr);

		ammunitionStr = this->getOrCreateElementString(doc, *currentWeapon, "amunitionsPerLoader", "");
		ammunition = std::stoi(ammunitionStr);

		fireRateStr = this->getOrCreateElementString(doc, *currentWeapon, "rateOfFire", "");
		fireRate = std::stof(fireRateStr);

		ammoPerShotStr = this->getOrCreateElementString(doc, *currentWeapon, "ammoPerShot", "");
		ammoPerShot = std::stoi(ammoPerShotStr);

		damageStr = this->getOrCreateElementString(doc, *currentWeapon, "damage", "");
		damage = std::stoi(damageStr);

		reloadTimeStr = this->getOrCreateElementString(doc, *currentWeapon, "reloadTime", "");
		reloadTime = std::stoi(reloadTimeStr);

		defaultAmunitionsStr = this->getOrCreateElementString(doc, *currentWeapon, "defaultAmunitions", "");
		defaultAmunitions = std::stoi(defaultAmunitionsStr);

		tinyxml2::XMLElement* fpsMetrics = this->getOrCreateElement(doc, *currentWeapon, "FPSMetrics");
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


		tinyxml2::XMLElement* externalMetrics = this->getOrCreateElement(doc, *currentWeapon, "FPSMetrics");
		if (fpsMetrics == nullptr)
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

		ecs::Weapon tmp(id, name, meshName, type, distance, precision, ammunition, fireRate, ammoPerShot, damage, reloadTime, ecs::Position(fpsMetricsPosition, fpsMetricsRotation, fpsMetricsScale), ecs::Position(externalMetricsPosition, externalMetricsRotation, externalMetricsScale), sight, defaultAmunitions);
		m_weapons.emplace(std::make_pair(type, tmp));
	}

	return true;
}

bool	WeaponsConfiguration::saveToFile(const std::string& filepath)	const
{
	throw std::logic_error("WeaponsConfiguration::saveToFile() not implemented");
}

const std::map<ecs::Weapon::WeaponType, ecs::Weapon>	&WeaponsConfiguration::getWeapons()	const
{
	return m_weapons;
}

ecs::Weapon::WeaponType	WeaponsConfiguration::parseWeaponType(const std::string& weaponTypeStr)	const
{
	std::map<std::string, ecs::Weapon::WeaponType>	weaponTypes;
	auto											weaponType = weaponTypes.end();

	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("SNIPER_RIFLE", ecs::Weapon::WeaponType::SNIPER_RIFLE));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("RAIL_GUN", ecs::Weapon::WeaponType::RAIL_GUN));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("SHOT_GUN", ecs::Weapon::WeaponType::SHOT_GUN));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("MACHINE_GUN", ecs::Weapon::WeaponType::MACHINE_GUN));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("PISTOL", ecs::Weapon::WeaponType::PISTOL));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("DOUBLE_PISTOL", ecs::Weapon::WeaponType::DOUBLE_PISTOL));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("SABRE", ecs::Weapon::WeaponType::SABRE));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("CHAINSAW", ecs::Weapon::WeaponType::CHAINSAW));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("KNIFE", ecs::Weapon::WeaponType::KNIFE));
	weaponType = weaponTypes.find(weaponTypeStr);
	if (weaponType != weaponTypes.end())
		return weaponType->second;
	else
		return ecs::Weapon::WeaponType::WEAPON_COUNT;
}
