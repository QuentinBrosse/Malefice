#include <iostream>
#include <irrlicht.h>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Irrlicht\Renderer.h>
#include <chrono>
#include "MainMenu.h"
#include "EventReceiver.h"
#include "LoadingWindows.h"
#include "WaitingRoom.h"
#include "InGameGUI.h"
#include "ConnectWindow.h"

#include "ClientCore.h"
#include "PlayerFactory.h"
#include "ProjectGlobals.h"
#include "CollectionComponent.h"
#include "Movement.h"
#include "MovementSystem.h"
#include "SpellSystem.h"
#include "WeaponSystem.h"
#include "Logger.h"

#include "NetworkModule.h"
#include "Logger.h"

#include "WeaponsConfiguration.h"
#include "SpellsConfiguration.h"

#define WIN_SIZE_X 1280
#define WIN_SIZE_Y 720

int main(int argc, char* argv[])
{
	Logger::getInstance().setup(ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH);
	ClientCore &core = ClientCore::getInstance();
	core.run();

	/*ClientCore	core;

	ecs::Entity	player = factory::PlayerFactory::createPlayer(1.0, 2.1, 0.0, 1, 1, 100);
	ecs::Entity predator = factory::PlayerFactory::createPredator(1.0, 4.2, 0.0, 2);
	ecs::Entity object = factory::ObjectFactory::createObject(2.0, 3.3, 0.0);

	core.addEntity(player);
	core.addEntity(predator);
	core.addEntity(object);

	core.dump();
	
	player[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(2.0, 3.1, 0.0));

	ecs::MovementSystem::move(player);
	ecs::SpellSystem::launchSpell(predator, player);
	ecs::WeaponSystem::shootOnTarget(player, 5, true, predator);

	core.dump();
	getchar();
	*/

	/*
	Logger::getInstance().setup(ProjectGlobals::GAME_CLIENT_CORE_LOG_FILEPATH);
	ClientCore::getInstance().run();

	WeaponsConfiguration	weaponsConfig;
	SpellsConfiguration		spellsConfig;
	std::map<ecs::Weapon::WeaponType, ecs::Weapon>	weapons;
	std::map<ecs::Spell::SpellType, ecs::Spell>	spells;

	weaponsConfig.loadFromFile(WeaponsConfiguration::WEAPONS_FILENAME);
	spellsConfig.loadFromFile(SpellsConfiguration::SPELLS_FILENAME);

	spells = spellsConfig.getSpells();
	weapons = weaponsConfig.getWeapons();

	for (auto pair : spells)
	{
		pair.second.dump();
	}

	for (auto pair : weapons)
	{
		pair.second.dump();
	}
	getchar();
	*/

	return (0);
}
