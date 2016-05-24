// Client Version

#include "WeaponSystem.h"
#include "SceneAnimatedMesh.h"
#include "GraphicUtil.h"

namespace ecs
{
	void				WeaponSystem::shoot(Entity& entity)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();

			if (weapon.getAmmunitions() > 0)
				weapon.shot();
			else
				weapon.reload();

			//TODO: sens to msg to server
		}
	}

	irr::core::line3df	WeaponSystem::getRay(Entity & entity)
	{
		WeaponManager*				weaponManager;
		irr::core::line3d<irr::f32> ray;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&					weapon = weaponManager->getCurrentWeapon();
			Camera*					camera = GraphicUtil::getInstance().getFPSCamera();

			weapon.getScene()->getScene()->updateAbsolutePosition();

			ray.start = weapon.getScene()->getScene()->getAbsolutePosition();
			ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * weapon.getDistance();
			ray.start += weapon.getFPSMetricsOffset();
			irr::core::vector3df vector(ray.end - ray.start);
			vector.normalize();
			ray.start += vector * weapon.getFPSMetricsCoefOffset();
		}
		return ray;
	}

}
