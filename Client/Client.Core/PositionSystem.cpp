// Client Version

#include "GraphicUtil.h"
#include "PositionSystem.h"
#include "SceneAnimatedMesh.h"
#include "Position.h"
#include "WeaponManager.h"
#include "AScene.h"
#include "MathUtility.h"
#include "ClientCore.h"

namespace ecs
{

	void PositionSystem::update(Entity& entity)
	{
		Position*		position;
		AScene*			scene;
		WeaponManager*	weaponManager;

		if ((position = dynamic_cast<Position*>(entity[ecs::AComponent::ComponentType::POSITION])) != nullptr && (scene = dynamic_cast<AScene*>(entity[ecs::AComponent::ComponentType::SCENE])) != nullptr)
		{
			// TODO: remove or update entity's position to others?
			Camera*	camera = GraphicUtil::getInstance().getFPSCamera();
			irr::core::vector3df posMe = position->getVectorPosition();
			irr::core::vector3df oriMe = position->getVectorRotation();
			irr::core::vector3df posCam = camera->getPosition().getVectorPosition();
			irr::core::vector3df oriCam = camera->getPosition().getVectorRotation();

			const float dist = 5.f;
			const float radCamY = utility::MathUtility::degreesToRadians(oriCam.Y);

			posCam.Y -= 27.f;
			posCam.X = posCam.X - dist * std::sin(radCamY);
			posCam.Z = posCam.Z - dist * std::cos(radCamY);
			oriMe.Y = oriCam.Y - 85.f;

			position->set(ecs::Position(posCam, oriMe));
			scene->setPosition(ecs::Position(posCam, oriMe));

			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_MANAGER_SERVER_UPDATE_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), entity.getOwner(), &entity);
		}

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])))
			weaponManager->getCurrentWeapon().setActivity(true);
	}

	void PositionSystem::initScenePosition(Entity& entity)
	{
		Position*	position;
		AScene*		scene;

		if ((position = dynamic_cast<Position*>(entity[ecs::AComponent::ComponentType::POSITION])) != nullptr && (scene = dynamic_cast<AScene*>(entity[ecs::AComponent::ComponentType::SCENE])) != nullptr)
		{
			scene->setPosition(*position);
		}
	}

}