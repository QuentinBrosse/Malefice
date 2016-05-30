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

	void WeaponManagerSystem::initFPSWeapon(Entity& entity)
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
				(*it).second.createScene(graphics.getDevice(), graphics.getDevice()->getSceneManager()->getActiveCamera(), false);
				scene = (*it).second.getScene();
				if (scene == nullptr) // DEBUG
					return;
				scene->setPosition((*it).second.getFPSMetrics());
			}

			if (weaponManager->hasCurrentWeapon())
				weaponManager->getCurrentWeapon().setActivity(true);
		}
	}

	void WeaponManagerSystem::initExternalWeapon(Entity& entity)
	{
		SceneAnimatedMesh*		sceneWeapon;
		SceneAnimatedMesh*		sceneplayer;
		WeaponManager*			weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr && (sceneplayer = dynamic_cast<SceneAnimatedMesh*>(entity[ecs::AComponent::ComponentType::SCENE])) != nullptr)
		{
			// TODO: remove or update entity's position to others?
			std::map<ecs::Weapon::WeaponType, Weapon>&	weapons = weaponManager->getWeapons();
			GraphicUtil&			graphics = GraphicUtil::getInstance();

			Camera*	camera = graphics.getFPSCamera();

			for (auto it = weapons.begin(); it != weapons.end(); ++it)
			{
				(*it).second.createScene(graphics.getDevice(), sceneplayer->getScene(), false);
				sceneWeapon = (*it).second.getScene();
				std::cout << (*it).second.getExternalMetrics() << std::endl;
				sceneWeapon->setPosition((*it).second.getExternalMetrics());
			}

			if (weaponManager->hasCurrentWeapon())
				weaponManager->getCurrentWeapon().setActivity(true);
		}

	}
}