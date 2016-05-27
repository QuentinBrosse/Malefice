#include	"SceneBillboardText.h"
#include	"Logger.h"
#include	"NodePickable.h"

namespace ecs
{

	SceneBillboardText::SceneBillboardText() : AScene(ecs::AScene::SceneType::BILLBOARD_TEXT),
		m_node(nullptr)
	{

	}

	SceneBillboardText::SceneBillboardText(const SceneBillboardText& cpy) : AScene(cpy),
		m_node(cpy.m_node)
	{
		LOG_DEBUG(GENERAL) << "Implement SceneBillboardText::SceneBillboardText(const SceneBillboardText &cpy)";
	}

	SceneBillboardText::SceneBillboardText(irr::IrrlichtDevice* device, const irr::video::SColor color, std::string text, const ecs::Position position) : AScene(ecs::AScene::SceneType::BILLBOARD_TEXT, device, "", "", nodePickable::NOT_PICKABLE, false),
		m_node(nullptr)
	{
		this->init(device, color, text, position);
	}

	SceneBillboardText::~SceneBillboardText()
	{
	}

	void	SceneBillboardText::init(irr::IrrlichtDevice* device, const irr::video::SColor color, std::string text, const ecs::Position position)
	{
		m_type = ecs::AScene::SceneType::BILLBOARD_TEXT;

		m_mediaPath = "";
		m_isCollisionable = false;

		m_selector = nullptr;
		m_device = device;
		m_smgr = device->getSceneManager();
		m_driver = device->getVideoDriver();
		m_nameTexture = "";
		m_nameMesh = "";
		m_pickableFlags = nodePickable::NOT_PICKABLE;
		m_material = nullptr;

		m_text = std::wstring(text.begin(), text.end());

		m_node = m_smgr->addBillboardTextSceneNode(nullptr, m_text.c_str());
		this->setPosition(position);
		m_node->setColor(color);
		m_node->setID(m_pickableFlags);
	}

	irr::scene::ISceneNode*	SceneBillboardText::getNode()	const
	{
		return m_node;
	}

	void	SceneBillboardText::setPosition(const ecs::Position& newPosition)
	{
		m_node->setPosition(newPosition.getVectorPosition());
		m_node->setSize(irr::core::dimension2d<irr::f32>(newPosition.getVectorScale().X, newPosition.getVectorScale().Y));
	}

	void	SceneBillboardText::setParent(irr::scene::ISceneNode* parent)
	{
		m_node->setParent(parent);
	}

	void	SceneBillboardText::dump(std::ostream& os)	const
	{
		os << "SceneBillboardText {}";
	}

	AComponent&	SceneBillboardText::affect(const AComponent & rhs)
	{
		const SceneBillboardText&	scene = dynamic_cast<const SceneBillboardText&>(rhs);

		m_text = scene.m_text;

		irr::video::SColor top;
		irr::video::SColor bottom;
		scene.m_node->getColor(top, bottom);
		m_node->setColor(top, bottom);
		m_node->setSize(scene.m_node->getSize());

		return *this;
	}

	AComponent* SceneBillboardText::createCopy(const AComponent * rhs) const
	{
		const SceneBillboardText* scene = dynamic_cast<const SceneBillboardText*>(rhs);

		return new SceneBillboardText(*scene);
	}

	void	SceneBillboardText::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AScene::serialize(out, serializeType);
	}

	void	SceneBillboardText::deserialize(RakNet::BitStream& in)
	{
		AScene::deserialize(in);
	}

}