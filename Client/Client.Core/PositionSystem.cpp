// Client Version

#include "GraphicUtil.h"
#include "PositionSystem.h"
#include "SceneAnimatedMesh.h"
#include "Position.h"
#include "WeaponManager.h"
#include "AScene.h"
#include "MathUtility.h"

namespace ecs
{

	void PositionSystem::update(Entity& entity)
	{
		Position*	position;
		AScene*		scene;

		if ((position = dynamic_cast<Position*>(entity[POSITION])) != nullptr && (scene = dynamic_cast<AScene*>(entity[SCENE])) != nullptr)
		{
			// TODO: remove or update entity's position to others?
			Camera*	camera = GraphicUtil::getInstance().getFPSCamera();
			irr::core::vector3df posMe = position->getVectorPosition();
			irr::core::vector3df oriMe = position->getVectorRotation();
			irr::core::vector3df posCam = camera->getPosition().getVectorPosition();
			irr::core::vector3df oriCam = camera->getPosition().getVectorRotation();

			const float dist = 5.f;
			const double pi = std::acos(-1);
			const float radCamY = utility::MathUtility::degreesToRadians(oriCam.Y);

			posCam.Y -= 27.f;
			posCam.X = posCam.X - dist * std::sin(radCamY);
			posCam.Z = posCam.Z - dist * std::cos(radCamY);
			oriMe.Y = oriCam.Y - 85.f;

			scene->setPosition(ecs::Position(posCam, oriMe));
		}
	}

	void PositionSystem::initWeapon(Entity & entity)
	{

		Position*				position;
		SceneAnimatedMesh*		scene;
		WeaponManager*			weaponManager;

		if ((position = dynamic_cast<Position*>(entity[POSITION])) != nullptr && (weaponManager = dynamic_cast<WeaponManager*>(entity[WEAPON_MANAGER])) != nullptr)
		{
			// TODO: remove or update entity's position to others?
			GraphicUtil&			graphics = GraphicUtil::getInstance();
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			scene = weapon.getScene();
			Camera*	camera = graphics.getFPSCamera();
		
			irr::core::vector3df	 scale = irr::core::vector3df(20.0f, 20.0f, 15.f);
			irr::core::vector3df	 position = irr::core::vector3df(1.2f, -0.8f, 1.5f);
			irr::core::vector3df	 rotation = irr::core::vector3df(0.f, 0.f, 0.f);
			
			weapon.createScene(graphics.getDevice(), "", "weapons/models/shotgun.obj", true);
			weapon.getScene()->setAnimation(irr::scene::EMAT_ATTACK);

			weapon.getScene()->getScene()->setScale(scale);
			weapon.getScene()->getScene()->setPosition(position);
			weapon.getScene()->getScene()->setRotation(rotation);
			//TODO: update position of weapon's scene
		}

	}

	void PositionSystem::initScenePosition(Entity & entity)
	{
		Position*	position;
		AScene*		scene;

		if ((position = dynamic_cast<Position*>(entity[POSITION])) != nullptr && (scene = dynamic_cast<AScene*>(entity[SCENE])) != nullptr)
		{
			scene->setPosition(*position);
		}
	}

}