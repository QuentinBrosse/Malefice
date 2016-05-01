#include "SpellSystem.h"

namespace ecs
{
	void SpellSystem::launchSpell(Entity& predator, Entity& target)
	{
		SpellManager*	spellManager;
		Spell*			spellOfTarget;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[SPELL_MANAGER])) != nullptr && (spellOfTarget = dynamic_cast<Spell*>(target[SPELL])) != nullptr)
		{
			if (spellOfTarget->getSpellType() == Spell::SpellType::NOTHING && !spellOfTarget->isLock())
			{
				Spell&	spellOfPredator = spellManager->getCurrentSpell();
				spellOfTarget->setSpellType(spellOfPredator.getSpellType());
				spellOfTarget->lock();
			}
		}
	}
}