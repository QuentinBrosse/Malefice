// Server Version

#include "SpellManagerSystem.h"
#include "SpellManager.h"
#include "ServerCore.h"

namespace ecs
{

	void SpellManagerSystem::changeSpell(Entity* predator, RakNet::RPC3* rpc)
	{
		ecs::Entity*		entity = ServerCore::getInstance().getPlayerManager().findEntity(predator->getOwner());
		ecs::SpellManager*	spellManagerLocal;
		ecs::SpellManager*	spellManagerClient;
	
		if ((spellManagerLocal = dynamic_cast<ecs::SpellManager*>((*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr
			&& (spellManagerClient = dynamic_cast<ecs::SpellManager*>((*predator)[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManagerLocal->affect(*spellManagerClient);
		}
	}
}