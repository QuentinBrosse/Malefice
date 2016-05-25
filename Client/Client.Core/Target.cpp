#include "Target.h"
#include "ClientCore.h"
#include "Irrlicht.h"
#include "Weapon.h"

Target::Target()
{
	m_graphicUtil = &GraphicUtil::getInstance();
	m_scene = new ecs::SceneBillboard();
	m_scene->init(m_graphicUtil->getDevice(), "particle.bmp", false, 0);
	m_playerManager = &PlayerManager::getInstance();
}

Target::~Target()
{
}

irr::core::line3df Target::getRay() const
{
	return m_ray;
}

void	Target::refresh()
{
	if (!m_playerManager->getCurrentPlayer())
		return;
	Camera*			camera = GraphicUtil::getInstance().getFPSCamera();
	ecs::Weapon&	weapon = dynamic_cast<ecs::WeaponManager*>((*m_playerManager->getCurrentPlayer())[ecs::AComponent::ComponentType::WEAPON_MANAGER])->getCurrentWeapon();

	if (weapon.getScene())
	{
		weapon.getScene()->getScene()->updateAbsolutePosition();
		m_ray.start = weapon.getScene()->getScene()->getAbsolutePosition();
		m_ray.end = m_ray.start + (camera->getTarget() - m_ray.start).normalize() * weapon.getDistance();
		m_ray.start += weapon.getFPSMetricsOffset();
		irr::core::vector3df vector(m_ray.end - m_ray.start);
		vector.normalize();
		m_ray.start += vector * weapon.getFPSMetricsCoefOffset();

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
			ecs::Position position(m_ray.end, irr::core::vector3df(0.F, 0.F, 0.F), irr::core::vector3df(20.F, 20.F, 0.F));
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