// Server Version

#include "SpellSystem.h"

namespace ecs
{
	void SpellSystem::launchSpell(Entity& predator)
	{
		SpellManager*	spellManager;
		Spell*			spellOfTarget;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			Spell&	spellOfPredator = spellManager->getCurrentSpell();
			//TODO: Ray Tracing, etc...
		}
	}
}