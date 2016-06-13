#pragma once

#include "EntityManager.h"
#include "Singleton.h"
#include "Entity.h"
#include <utility>
#include <map>
#include "Team.h"

// TODO: do we really need a PlayerManager or is an EntityManager enough?
class PlayerManager : public EntityManager, public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

public:
	virtual void	addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc);

	void			initPlayersScene();

	void			initPlayersWeapons();

	ecs::Entity*	getCurrentPlayer()	const;
	void			setCurrentPlayer(ecs::Entity* localPlayer);
	const std::map<ecs::ClientId, ecs::Entity*> &getEntities() const;

	int				getTeam1Score();
	int				getTeam2Score();
	int				getPredatorScore();

	void			loadNormalTeamTexture();
	void			loadInvertTeamTexture();

	void			removeWeaponScene();
	
	void			checkTexturePredator();

	std::map<std::string, std::pair<int, ecs::Team::TeamType>>	getPlayersScore();


protected:
	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager()					= default;


private:
	std::vector<std::string>						m_predatorTextures;
	int												m_predatorStades;

private:
	ecs::Entity*									m_currentPlayer;
};
