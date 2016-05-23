// Client Version

#include "WeaponManagerSystem.h"
#include "WeaponManager.h"
#include "GraphicUtil.h"

namespace ecs
{

	void WeaponManagerSystem::changeToNext(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			weaponManager->changeToNextWeapon();
			// TODO: send msg to server
		}
	}

	void WeaponManagerSystem::changeToPrec(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			weaponManager->changeToPrecWeapon();
			// TODO: send msg to server
		}
	}

	void WeaponManagerSystem::initWeapon(Entity& entity)
	{
		SceneAnimatedMesh*		scene;
		WeaponManager*			weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			// TODO: remove or update entity's position to others?
			std::map<ecs::Weapon::WeaponType, Weapon>&	weapons = weaponManager->getWeapons();
			GraphicUtil&			graphics = GraphicUtil::getInstance();

			Camera*	camera = graphics.getFPSCamera();

			for (auto it = weapons.begin(); it != weapons.end(); ++it)
			{
				(*it).second.createScene(graphics.getDevice(), false);
				scene = (*it).second.getScene();

				scene->setPosition((*it).second.getFPSMetrics());
			}

			if (weaponManager->hasCurrentWeapon())
				weaponManager->getCurrentWeapon().setActivity(true);
		}
	}

	void WeaponManagerSystem::attachCamera(Entity& entity)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			GraphicUtil&	graphics = GraphicUtil::getInstance();

			for (auto weapon : weaponManager->getWeapons())
			{
				weapon.second.createScene(graphics.getDevice(), false);
				graphics.getSceneManager()->getActiveCamera()->addChild(weapon.second.getScene()->getScene());
			}
		}
	}
}