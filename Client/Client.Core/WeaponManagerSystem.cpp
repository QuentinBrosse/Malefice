// Client Version

#include "WeaponManagerSystem.h"
#include "GraphicUtil.h"
#include "SpellManager.h"

namespace ecs
{
	void WeaponManagerSystem::changeToNext(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr && weaponManager->hasCurrentWeapon())
		{
			irr::scene::ISceneNode* parent = weaponManager->getCurrentWeapon().getScene()->getNode()->getParent();
			irr::core::vector3df pos = weaponManager->getCurrentWeapon().getScene()->getNode()->getPosition();

			weaponManager->changeToNextWeapon();
			if (!weaponManager->getCurrentWeapon().getScene())
			{
				weaponManager->getCurrentWeapon().createScene(GraphicUtil::getInstance().getDevice(), nullptr, true);
				weaponManager->getCurrentWeapon().getScene()->getNode()->setParent(parent);
				weaponManager->getCurrentWeapon().getScene()->setPosition(weaponManager->getCurrentWeapon().getFPSMetrics());
			}
			if (weaponManager->getWeapons().size() > 1)
			{
				ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::WEAPON_MANAGER_SYSTEM_CHANGE_NEXT, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponManagerSystem), &player);
			}
			Sleep(25);
			PositionSystem::updateScenePosition(player);
		}
	}

	void WeaponManagerSystem::changeToPrec(Entity& player)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(player[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			irr::scene::ISceneNode* parent = weaponManager->getCurrentWeapon().getScene()->getNode()->getParent();
			irr::core::vector3df pos = weaponManager->getCurrentWeapon().getScene()->getNode()->getPosition();

			weaponManager->changeToPrecWeapon();
			if (!weaponManager->getCurrentWeapon().getScene())
			{
				weaponManager->getCurrentWeapon().createScene(GraphicUtil::getInstance().getDevice(), dynamic_cast<ecs::SceneAnimatedMesh*>((player)[ecs::AComponent::ComponentType::SCENE])->getNode(), true);
				weaponManager->getCurrentWeapon().getScene()->getNode()->setParent(parent);
				weaponManager->getCurrentWeapon().getScene()->setPosition(weaponManager->getCurrentWeapon().getFPSMetrics());

//				weaponManager->getCurrentWeapon().getScene()->setPosition(ecs::Position(pos, irr::core::vector3df(0, 0, 0), irr::core::vector3df(20.F, 20.F, 15.F)));
			}
			if (weaponManager->getWeapons().size() > 1)
			{
				ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::WEAPON_MANAGER_SYSTEM_CHANGE_PREC, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponManagerSystem), &player);
			}
			Sleep(25);
			PositionSystem::updateScenePosition(player);
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
				if (it->second.getScene() == nullptr)
				{
					(*it).second.createScene(graphics.getDevice(), graphics.getDevice()->getSceneManager()->getActiveCamera(), false);
					scene = (*it).second.getScene();
					if (scene == nullptr) // DEBUG
						return;
					scene->setPosition((*it).second.getFPSMetrics());
				}
				it->second.setActivity(false);
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
				if (it->second.getScene() == nullptr)
				{
					(*it).second.createScene(graphics.getDevice(), sceneplayer->getScene(), false);
					sceneWeapon = (*it).second.getScene();
					sceneWeapon->setPosition((*it).second.getExternalMetrics());
				}
				it->second.setActivity(false);
			}

			if (weaponManager->hasCurrentWeapon())
				weaponManager->getCurrentWeapon().setActivity(true);
		}

	}

	void WeaponManagerSystem::setCurrentWeaponVisibility(Entity & entity)
	{
		WeaponManager*	weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr && weaponManager->hasCurrentWeapon())
			weaponManager->getCurrentWeapon().setActivity(true);
	}

	
}