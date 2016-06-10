// Client Version

#include "SpellManagerSystem.h"
#include "SpellManager.h"
#include "GraphicUtil.h"
#include "SceneAnimatedMesh.h"

namespace ecs
{

	void SpellManagerSystem::changeToNext(Entity& predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeToNextSpell();
			// TODO : Send msg to server
		}
	}

	void SpellManagerSystem::changeToPrec(Entity & predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeToPrecSpell();
			// TODO : Send msg to server
		}
	}

	void SpellManagerSystem::changeManager(Entity & predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeCurrentManager();
			// TODO : Send msg to server
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