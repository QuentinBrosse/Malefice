#include "WeaponSystem.h"
#include "SceneAnimatedMesh.h"
#include "GraphicUtil.h"
#include "ClientCore.h"

namespace ecs
{
	void				WeaponSystem::shoot(Entity& entity)
	{
		WeaponManager*		weaponManager;
		irr::core::line3df	ray;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			ray = WeaponSystem::getRay(weapon);
			weapon.setRay(ray);
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::WEAPON_SYSTEM_SHOOT, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), &entity);
		}
	}

	irr::core::line3df	WeaponSystem::getRay(Weapon& weapon)
	{
		irr::core::line3df	ray;
		Camera*				camera = GraphicUtil::getInstance().getFPSCamera();

		weapon.getScene()->getScene()->updateAbsolutePosition();

		ray.start = weapon.getScene()->getScene()->getAbsolutePosition();
		ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * weapon.getDistance();
		ray.start += weapon.getFPSMetricsOffset();
		irr::core::vector3df vector(ray.end - ray.start);
		vector.normalize();
		ray.start += vector * weapon.getFPSMetricsCoefOffset();
		return ray;
	}

}
