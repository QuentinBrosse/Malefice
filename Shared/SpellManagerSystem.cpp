#include "SpellManagerSystem.h"
#include "SpellManager.h"

namespace ecs
{

	void SpellManagerSystem::changeToNext(Entity& predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[SPELL_MANAGER])) != nullptr)
			spellManager->changeToNextSpell();
	}

	void SpellManagerSystem::changeToPrec(Entity & predator)
	{
		SpellManager*	spellManager;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[SPELL_MANAGER])) != nullptr)
			spellManager->changeToPrecSpell();
	}

}