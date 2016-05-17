#include "SpellSystem.h"

// Client Version

namespace ecs
{
	void SpellSystem::launchSpell(Entity& predator)
	{
		SpellManager*	spellManager;
		Spell*			spellOfTarget;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			Spell&	spellOfPredator = spellManager->getCurrentSpell();
			//TODO: Send msg to server
		}
	}
}