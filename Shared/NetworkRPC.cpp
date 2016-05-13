#include "NetworkRPC.h"

/*
** These strings are just IDENTIFIERS of the RPCs.
** Below the function names are used as identifiers but it would work with any string,
** as long as the identifier and the function are correctly bound using RPC3::RegisterFunction()
*/


// Client-Side executed

const std::string	NetworkRPC::CLIENT_CORE_SET_CLIENT_ID	= "ClientCore::setClientId";

const std::string	NetworkRPC::PLAYER_MANAGER_ADD_ENTITY		= "PlayerManager::addEntity";
const std::string	NetworkRPC::PLAYER_MANAGER_REMOVE_ENTITY	= "PlayerManager::removeEntity";


// Server-Side executed

