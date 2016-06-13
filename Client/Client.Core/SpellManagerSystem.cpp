// Client Version

#include "SpellManagerSystem.h"
#include "SpellManager.h"
#include "GraphicUtil.h"
#include "SceneAnimatedMesh.h"
#include "ClientCore.h"
#include "NetworkRPC.h"

namespace ecs
{

	void SpellManagerSystem::changeToNext(Entity& predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeToNextSpell();
			if (spellManager->getSpells().size() > 1)
			{
				ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_MANAGER_SYSTEM_CHANGE_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellManagerSystem), &predator);
			}
		}
	}

	void SpellManagerSystem::changeToPrec(Entity & predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeToPrecSpell();
			if (spellManager->getSpells().size() > 1)
			{
				ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_MANAGER_SYSTEM_CHANGE_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellManagerSystem), &predator);
			}
		}
	}

	void SpellManagerSystem::changeManager(Entity & predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeCurrentManager();
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_MANAGER_SYSTEM_CHANGE_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellManagerSystem), &predator);
		}
	}

	void SpellManagerSystem::initFPSScene(Entity & predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->createFPSScene(GraphicUtil::getInstance().getDevice(), GraphicUtil::getInstance().getSceneManager()->getActiveCamera());
		}
	}

	void SpellManagerSystem::removeScene(Entity & entity)
	{
		SceneAnimatedMesh*		scene;
		SpellManager*			spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(entity[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			std::map<ecs::Spell::SpellType, Spell>&	spells = spellManager->getSpells();
			std::map<ecs::Weapon::WeaponType, ecs::Weapon>& weapons = spellManager->getWeapons();

			for (auto it = spells.begin(); it != spells.end(); ++it)
			{
				if (it->second.getScene() != nullptr)
					(*it).second.deleteScene();
			}
			for (auto it = weapons.begin(); it != weapons.end(); ++it)
			{
				if (it->second.getScene() != nullptr)
					(*it).second.deleteScene();
			}
		}
	}
}