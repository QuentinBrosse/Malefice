#include "NetworkRPC.h"


const RakNet::NetworkID	NetworkRPC::GENERAL_RPC_ID	= 0;
const RakNet::NetworkID	NetworkRPC::PLAYER_RPC_ID	= 1;


const std::string	NetworkRPC::PLAYER_CONNECT		= "RPC_PlayerConnect";
const std::string	NetworkRPC::PLAYER_DISCONNECT	= "RPC_PlayerDisconnect";
const std::string	NetworkRPC::PLAYER_SYNC			= "RPC_PlayerSync";

const std::string	NetworkRPC::PLAYER_ADD		= "RPC_PlayerAdd";
const std::string	NetworkRPC::PLAYER_REMOVE	= "RPC_PlayerRemove";

const std::string	NetworkRPC::PLAYER_CHAT	= "RPC_PlayerChat";
