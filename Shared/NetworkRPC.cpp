#include "NetworkRPC.h"

/*
** These strings are just IDENTIFIERS of the RPCs.
** Below the function names are used as identifiers but it would work with any string,
** as long as the identifier and the function are correctly bound using RPC3::RegisterFunction()
*/


// Client-Side executed

const std::string	NetworkRPC::CLIENT_CORE_SET_CLIENT_ID			= "ClientCore::setClientId";
const std::string	NetworkRPC::CLIENT_CORE_NOTIFY_INVALID_NICKNAME	= "ClientCore::notifyInvalidNickname";
const std::string	NetworkRPC::CLIENT_CORE_START_GAME				= "ClientCore::startGame";

const std::string	NetworkRPC::PLAYER_MANAGER_ADD_ENTITY		= "PlayerManager::addEntity";
const std::string	NetworkRPC::PLAYER_MANAGER_UPDATE_ENTITY	= "PlayerManager::updateEntity";
const std::string	NetworkRPC::PLAYER_MANAGER_REMOVE_ENTITY	= "PlayerManager::removeEntity";

const std::string	NetworkRPC::SPAWNER_MANAGER_ADD_ENTITY		= "SpawnerManager::addEntity";
const std::string	NetworkRPC::SPAWNER_MANAGER_UPDATE_ENTITY	= "SpawnerManager::updateEntity";
const std::string	NetworkRPC::SPAWNER_MANAGER_REMOVE_ENTITY	= "SpawnerManager::removeEntity";

const std::string	NetworkRPC::LIFE_SYSTEM_DIE	= "LifeSystem::die";

const std::string	NetworkRPC::TRIGGER_SHOOT_ACTIONS = "WeaponSystem::triggerShootActions";
// Server-Side executed

const std::string	NetworkRPC::PLAYER_MANAGER_SET_PLAYER_NICKNAME	= "PlayerManager::setPlayerNickname";
const std::string	NetworkRPC::PLAYER_MANAGER_SERVER_UPDATE_ENTITY = "PlayerManager::updateEntity";

const std::string	NetworkRPC::WEAPON_SYSTEM_SHOOT	= "WeaponSystem::shoot";

const std::string	NetworkRPC::WEAPON_MANAGER_SYSTEM_CHANGE_NEXT = "WeaponManagerSystem::changeToNext";
const std::string	NetworkRPC::WEAPON_MANAGER_SYSTEM_CHANGE_PREC = "WeaponManagerSystem::changeToPrec";

const std::string	NetworkRPC::SPAWNER_MANAGER_COLLISION_DETECTION = "SpawnerManager::collisionDetection";
const std::string	NetworkRPC::SPELL_SYSTEM_LAUNCH_SPELL	= "SpellSystem::launchSpell";
