// CLIENT VERSION

#include "WeaponSystem.h"
#include "SceneAnimatedMesh.h"
#include "GraphicUtil.h"
#include "ClientCore.h"
#include "Target.h"
#include "Line3dWrapper.h"
#include "Audio.h"

namespace ecs
{
	void	WeaponSystem::shoot(Entity& entity)
	{
		WeaponManager*		weaponManager;
		ecs::Position*		playerPosition;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
		  Line3dWrapper	line3dWrapper{Target::getInstance().getRay()};

			playerPosition = dynamic_cast<ecs::Position*>(entity[ecs::AComponent::ComponentType::POSITION]);
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			Target::getInstance().refresh();
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::WEAPON_SYSTEM_SHOOT, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), &entity, &line3dWrapper);
		}
	}

	void WeaponSystem::triggerShootActions(Entity* entity, int status, RakNet::RPC3 * rpc)
	{
		WeaponManager*		weaponManager;
		ecs::Position*		playerPosition;

		if ((weaponManager = dynamic_cast<WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			playerPosition = dynamic_cast<ecs::Position*>((*entity)[ecs::AComponent::ComponentType::POSITION]);
			Weapon&	weapon = weaponManager->getCurrentWeapon();

			switch (status)
			{
			case 0:
				Audio::getInstance().play3D(weapon.getAudioShot(), *playerPosition);
				break;
			case 1:
				Audio::getInstance().play3D(weapon.getAudioReload(), *playerPosition);
				break;
			default:
				Audio::getInstance().play3D("empty.ogg", *playerPosition);
				break;
			}
		}
	}

	void WeaponSystem::zoom(Entity& entity)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[AComponent::ComponentType::WEAPON_MANAGER])) != nullptr
			&& weaponManager->hasCurrentWeapon()
			&& weaponManager->getCurrentWeapon().getWeaponType() == Weapon::WeaponType::SNIPER_RIFLE)
		{
			Camera*	camera = GraphicUtil::getInstance().getFPSCamera();

			if (camera->isInZoom())
				camera->unZoom();
			else
				camera->zoom();
		}
	}

}
