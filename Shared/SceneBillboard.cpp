#include "SceneBillboard.h"
#include "Logger.h"
#include "NodePickable.h"

namespace ecs
{
	SceneBillboard::SceneBillboard() : AScene(ecs::AScene::SceneType::BILLBOARD),
		m_node(nullptr)
	{
	}

	SceneBillboard::SceneBillboard(const SceneBillboard & cpy) : AScene(cpy),
		m_node(cpy.m_node)
	{
		LOG_DEBUG(GENERAL) << "Implement SceneBillboard::SceneBillboard(const SceneBillboard & cpy)";
	}

	SceneBillboard::SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh): AScene(ecs::AScene::SceneType::BILLBOARD, device, newNameTexture, newNameMesh, nodePickable::NOT_PICKABLE, false),
		m_node(nullptr)
	{
		this->init(device, newNameTexture, false, 0);
	}

	SceneBillboard::~SceneBillboard()
	{
	}

	void	SceneBillboard::init(irr::IrrlichtDevice* device, const std::string& newNameTexture, const bool lighting, const irr::u32 level)
	{
		m_type = SceneType::BILLBOARD;
		m_device = device;
		m_smgr = m_device->getSceneManager();
		m_driver = m_device->getVideoDriver();
		m_nameTexture = newNameTexture;
		m_level = level;
		m_lighting = lighting;
		m_material = nullptr;
		m_node = m_smgr->addBillboardSceneNode();
		m_pickableFlags = nodePickable::NOT_PICKABLE;

		m_material = new irr::video::SMaterial();

		if (newNameTexture != "")
			this->setTexture(newNameTexture);

		m_node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		
		m_node->setColor(irr::video::SColor(255, 255, 255, 255), irr::video::SColor(255, 255, 0, 0));
		m_node->setMaterialFlag(irr::video::EMF_LIGHTING, m_lighting);
		m_node->setMaterialFlag(irr::video::EMF_ZBUFFER, false);

		Position position(irr::core::vector3df(0.F, 0.F, 0.F), irr::core::vector3df(0.F, 0.F, 0.F), irr::core::vector3df(20.F, 20.F, 0.F));
		this->setPosition(position);

		m_node->setID(m_pickableFlags);
	}


	irr::scene::ISceneNode*	SceneBillboard::getNode()	const
	{
		return m_node;
	}

	void	SceneBillboard::setPosition(const ecs::Position& newPosition)
	{
		m_node->setPosition(newPosition.getVectorPosition());
		m_node->setRotation(newPosition.getVectorRotation());
		m_node->setScale(newPosition.getVectorScale());
		m_node->setSize(irr::core::dimension2d<irr::f32>(newPosition.getVectorScale().X, newPosition.getVectorScale().Y));
	}

	void	SceneBillboard::setTexture(const std::string& nameTexture)
	{
		m_node->setMaterialTexture(m_level, m_driver->getTexture((m_mediaPath + nameTexture).c_str()));
		m_nameTexture = nameTexture;
	}

	void	SceneBillboard::dump(std::ostream& os)	const
	{
		os << "SceneBillboard {}";
	}

	AComponent & SceneBillboard::affect(const AComponent & rhs)
	{
		const SceneBillboard&	scene = dynamic_cast<const SceneBillboard&>(rhs);

		m_nameMesh = scene.m_nameMesh;
		m_nameTexture = scene.m_nameTexture;
		m_type = scene.m_type;
		return *this;
	}

	AComponent* SceneBillboard::createCopy(const AComponent * rhs) const
	{
		const SceneBillboard* scene = dynamic_cast<const SceneBillboard*>(rhs);

		return new SceneBillboard(*scene);
	}

	void	SceneBillboard::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AScene::serialize(out, serializeType);
	}

	void	SceneBillboard::deserialize(RakNet::BitStream& in)
	{
		AScene::deserialize(in);
	}

	irr::scene::IBillboardSceneNode * SceneBillboard::getScene() const
	{
		return m_node;
	}

}
