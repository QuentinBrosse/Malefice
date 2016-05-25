#include "SpellSystem.h"
#include "ClientCore.h"
#include "WeaponSystem.h"

namespace ecs
{
	void SpellSystem::launchSpell(Entity& predator)
	{
		SpellManager*	spellManager;
		Spell*			spellOfTarget;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			irr::core::line3df	ray;

			Spell&	spellOfPredator = spellManager->getCurrentSpell();
			Weapon&	weapon = spellManager->getCurrentWeapon();
			ray = WeaponSystem::getRay(weapon);
			weapon.setRay(ray);
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_SYSTEM_LAUNCH_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellSystem), &predator);
		}
	}
}
