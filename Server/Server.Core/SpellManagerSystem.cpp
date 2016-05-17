// Server Version

#include "SpellManagerSystem.h"
#include "SpellManager.h"

namespace ecs
{

	void SpellManagerSystem::changeToNext(Entity& predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeToNextSpell();
			// TODO: update ?
		}
	}

	void SpellManagerSystem::changeToPrec(Entity & predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			spellManager->changeToPrecSpell();
			// TODO: update ?
		}
	}

}