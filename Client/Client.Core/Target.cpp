#include <irrlicht.h>
#include "Target.h"
#include "ClientCore.h"
#include "Weapon.h"
#include "IrrlichtUtility.h"
#include "SpellManager.h"
#include "Team.h"

Target::Target()
{
	m_graphicUtil = &GraphicUtil::getInstance();
	m_scene = new ecs::SceneBillboard();
	m_scene->init(m_graphicUtil->getDevice(), "particle.bmp", false, 0);
	m_playerManager = &PlayerManager::getInstance();
	m_isTrembling = false;
}

Target::~Target()
{
}

const irr::core::line3df& Target::getRay() const
{
	return m_ray;
}

void Target::setIsTrembling(const bool isTrembling)
{
	m_isTrembling = isTrembling;
}

void	Target::refresh()
{
	if (!m_playerManager->getCurrentPlayer())
		return;
	ecs::Weapon*	weapon;
	Camera*			camera = GraphicUtil::getInstance().getFPSCamera();
	if (dynamic_cast<ecs::Team*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::TEAM])->getTeam() != ecs::Team::TeamType::Predator)
		weapon = &dynamic_cast<ecs::WeaponManager*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::WEAPON_MANAGER])->getCurrentWeapon();
	else
		weapon = &dynamic_cast<ecs::SpellManager*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::SPELL_MANAGER])->getCurrentWeapon();

	if (weapon->getScene())
	{
		weapon->getScene()->getScene()->updateAbsolutePosition();
		m_ray.start = weapon->getScene()->getScene()->getAbsolutePosition();
		m_ray.end = m_ray.start + (camera->getTarget() - m_ray.start).normalize() * weapon->getDistance();
		m_ray.start += weapon->getFPSMetricsOffset();
		irr::core::vector3df vector(m_ray.end - m_ray.start);
		vector.normalize();
		m_ray.start += vector * weapon->getFPSMetricsCoefOffset();

		if (m_isTrembling)
		{
			int a = std::rand() % 5;
			switch (a)
			{
			case 0:
				m_ray.end.X += 15;
				break;
			case 1:
				m_ray.end.X -= 15;
				break;
			case 2:
				m_ray.end.Y += 15;
				break;
			case 3:
				m_ray.end.Y -= 15;
				break;
			case 4:
				m_ray.end.Z += 15;
				break;
			case 5:
				m_ray.end.Z -= 15;
				break;
			}
		}
		irr::core::vector3df intersection;
		irr::core::triangle3df hitTriangle;
		irr::scene::ISceneNode* selectedSceneNode =
			m_graphicUtil->getSceneManager()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
				m_ray,
				intersection,
				hitTriangle,
				nodePickable::IS_PICKABLE,
				0);

		if (selectedSceneNode)
		{
			m_scene->getNode()->setVisible(true);
			m_scene->getNode()->setPosition(intersection);
		}
		else
		{
			m_scene->getNode()->setVisible(false);
		}
	}

}

void	Target::debugDrawRay() const
{
	irr::video::IVideoDriver* driver = GraphicUtil::getInstance().getDriver();

	driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);

	irr::video::SMaterial mat;
	mat.Lighting = false;
	driver->setMaterial(mat);
	driver->draw3DLine(m_ray.start, m_ray.end);
}