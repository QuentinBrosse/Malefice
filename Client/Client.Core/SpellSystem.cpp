// CLIENT VERSION

#include "SpellSystem.h"
#include "ClientCore.h"
#include "WeaponSystem.h"
#include "Target.h"
#include "Line3dWrapper.h"

namespace ecs
{
	void SpellSystem::launchSpell(Entity& predator)
	{
		SpellManager*	spellManager;
		Spell*			spellOfTarget;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{

			Spell&	spellOfPredator = spellManager->getCurrentSpell();
			Target::getInstance().refresh();
			//TODO : Move Target::getRay to RPC argument
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_SYSTEM_LAUNCH_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellSystem), &predator, &Line3dWrapper(Target::getInstance().getRay()));
		}
	}
}
