// CLIENT VERSION

#include "SpellSystem.h"
#include "ClientCore.h"
#include "WeaponSystem.h"
#include "Target.h"
#include "Line3dWrapper.h"
#include "Audio.h"

namespace ecs
{
	Spell::SpellType	SpellSystem::lastSpellType = Spell::SpellType::NOTHING;

	void SpellSystem::launchSpell(Entity& predator)
	{
		SpellManager*	spellManager;
		Spell*			spellOfTarget;

		if ((spellManager = dynamic_cast<SpellManager*>(predator[ecs::AComponent::ComponentType::SPELL_MANAGER])) != nullptr)
		{
			Spell&	spellOfPredator = spellManager->getCurrentSpell();
			Target::getInstance().refresh();
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_SYSTEM_LAUNCH_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellSystem), &predator, &Line3dWrapper(Target::getInstance().getRay()));
		}
	}

	void SpellSystem::affect(Entity& entity)
	{
		Spell*	spell;

		if ((spell = dynamic_cast<Spell*>(entity[ecs::AComponent::ComponentType::SPELL])) != nullptr)
		{
			Spell::SpellType	spellType = spell->getSpellType();
			if (spellType == lastSpellType)
				return;
			GraphicUtil&	graphics = GraphicUtil::getInstance();
			ecs::Position cameraPosition(graphics.getSceneManager()->getActiveCamera()->getAbsolutePosition(),
										graphics.getSceneManager()->getActiveCamera()->getTarget());
			if (spellType == Spell::SpellType::NOTHING)
			{
				switch (lastSpellType)
				{
				case ecs::Spell::BLIND:
					graphics.getBlindFx()->hide();
					break;
				case ecs::Spell::PARANOIA:
					PlayerManager::getInstance().loadNormalTeamTexture();
					break;
				case ecs::Spell::CONFUSION:
					graphics.getFPSCamera()->loadKey(cameraPosition, graphics.getSceneManager(), true);
					break;
				case ecs::Spell::DEAF:
					Audio::getInstance().setIsDeaf(false);
					break;
				case ecs::Spell::PARKINSON:
					Target::getInstance().setIsTrembling(false);
					break;
				case ecs::Spell::SLOW:
					break;
				default:
					break;
				}
			}
			else
			{
				switch (spellType)
				{
				case ecs::Spell::BLIND:
					GraphicUtil::getInstance().getBlindFx()->display();
					break;
				case ecs::Spell::PARANOIA:
					PlayerManager::getInstance().loadInvertTeamTexture();
					break;
				case ecs::Spell::CONFUSION:
					graphics.getFPSCamera()->loadKey(cameraPosition, graphics.getSceneManager(), false);
					break;
				case ecs::Spell::DEAF:
					Audio::getInstance().setIsDeaf(true);
					break;
				case ecs::Spell::PARKINSON:
					Target::getInstance().setIsTrembling(true);
					break;
				case ecs::Spell::SLOW:
					break;
				default:
					break;
				}
			}
			lastSpellType = spellType;
		}
	}
}
