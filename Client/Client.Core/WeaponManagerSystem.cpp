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
			std::map<ecs::Weapon::WeaponType, Weapon&>&	weapons = weaponManager->getWeapons();
			GraphicUtil&			graphics = GraphicUtil::getInstance();

			Camera*	camera = graphics.getFPSCamera();

			/*
			irr::core::vector3df	 scale = irr::core::vector3df(20.0f, 20.0f, 15.f);
			irr::core::vector3df	 position = irr::core::vector3df(1.2f, -0.8f, 1.5f);
			irr::core::vector3df	 rotation = irr::core::vector3df(0.f, 0.f, 0.f);
			*/

			for (auto weapon : weapons)
			{
				scene = weapon.second.getScene();

				weapon.second.getScene()->setPosition(weapon.second.getFPSMetrics());
				/*
				weapon.second.getScene()->getScene()->setScale(scale);
				weapon.second.getScene()->getScene()->setPosition(position);
				weapon.second.getScene()->getScene()->setRotation(rotation);
				*/
			}

			weaponManager->getCurrentWeapon().setActivity(true);

			//TODO: update position of weapon's scene
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
//				irr::scene::ISceneNode*	aaa = weapon.second.getScene()->getScene()->getParent();
				weapon.second.createScene(graphics.getDevice(), false);
				graphics.getSceneManager()->getActiveCamera()->addChild(weapon.second.getScene()->getScene());
	//			irr::scene::ISceneNode*	bbb = weapon.second.getScene()->getScene()->getParent();
			}
		}
	}
}