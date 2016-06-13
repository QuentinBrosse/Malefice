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
		  Line3dWrapper	line3dWrapper{Target::getInstance().getRay()};
		  irr::core::line3df ray = line3dWrapper.getLine();
		  irr::scene::ISceneNodeAnimator* anim = 0;

		  Spell&	spellOfPredator = spellManager->getCurrentSpell();
		 
		  Target::getInstance().refresh();
		  ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPELL_SYSTEM_LAUNCH_SPELL, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpellSystem), &predator, &line3dWrapper);
		 
		  irr::f32 length = (irr::f32)(ray.end - ray.start).getLength();
		  const irr::f32 speed = 0.1f;
		  irr::u32 time = (irr::u32)((length / 1.5) / speed);

		  irr::scene::IAnimatedMesh* mesh = GraphicUtil::getInstance().getSceneManager()->getMesh(std::string("Media/spells/models/" + spellOfPredator.getMeshName()).c_str());
		  irr::scene::ISceneNode* node = GraphicUtil::getInstance().getSceneManager()->addMeshSceneNode(mesh, nullptr, 19, ray.start);
		  node->setScale(spellOfPredator.getScene()->getNode()->getScale());
		  node->setRotation(spellOfPredator.getScene()->getNode()->getRotation());
		  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		  anim = GraphicUtil::getInstance().getSceneManager()->createFlyStraightAnimator(ray.start, ray.end, time, false, false);
		  node->addAnimator(anim);	
		  anim->drop();

		  anim = GraphicUtil::getInstance().getSceneManager()->createDeleteAnimator(time);
		  node->addAnimator(anim);
		  anim->drop();
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
					graphics.getFPSCamera()->loadDefaultKeys();
					break;
				case ecs::Spell::DEAF:
					Audio::getInstance().setIsDeaf(false);
					break;
				case ecs::Spell::PARKINSON:
					Target::getInstance().setIsTrembling(false);
					break;
				case ecs::Spell::SLOW:
					graphics.getFPSCamera()->setSpeed(0.5f, 100.0f);
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
					graphics.getFPSCamera()->loadInvertKeys();
					break;
				case ecs::Spell::DEAF:
					Audio::getInstance().setIsDeaf(true);
					break;
				case ecs::Spell::PARKINSON:
					Target::getInstance().setIsTrembling(true);
					break;
				case ecs::Spell::SLOW:
					graphics.getFPSCamera()->setSpeed(0.1f, 50.0f);
					break;
				default:
					break;
				}
			}
			lastSpellType = spellType;
		}
	}
}
