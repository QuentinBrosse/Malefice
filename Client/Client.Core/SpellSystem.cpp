#include "SpellSystem.h"
#include "ClientCore.h"
#include "WeaponSystem.h"
#include "Target.h"

namespace ecs
{
	void SpellSystem::launchSpell(Entity& predator)
	{
		SpellManager*	spellManager;
		Spell*			spellOfTarget;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{

			Spell&	spellOfPredator = spellManager->getCurrentSpell();
			spellManager->getCurrentWeapon().setRay(&Target::getInstance().getRay());
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_SYSTEM_LAUNCH_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellSystem), &predator);
		}
	}
}
