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
}