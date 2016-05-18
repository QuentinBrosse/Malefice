#include <iterator>
#include "Entity.h"
#include "Armor.h"
#include "GameEventReceiver.h"
#include "Life.h"
#include "Movement.h"
#include "PlayerInfos.h"
#include "Position.h"
#include "AScene.h"
#include "SceneMesh.h"
#include "SceneAnimatedMesh.h"
#include "SceneBillboard.h"
#include "Spell.h"
#include "SpellManager.h"
#include "Team.h"
#include "Weapon.h"
#include "WeaponManager.h"

namespace ecs
{
	Entity::Entity() :
		m_owner(0), m_entityType(EntityType::NOTHING), m_components()
	{
	}

	Entity::Entity(ecs::ClientId owner, EntityType entityType) :
		m_owner(owner), m_entityType(entityType), m_components()
	{
	}

	Entity::~Entity()
	{
		for (auto component : m_components)
		{
			delete component.second;
		}
	}



	bool	Entity::has(ecs::AComponent::ComponentType type)	const
	{
		try
		{
			m_components.at(type);
			return true;
		}

		catch (const std::exception&)
		{
			return false;
		}
	}

	ecs::ClientId	Entity::getOwner()	const
	{
		return m_owner;
	}

	ecs::Entity::EntityType	Entity::getEntityType()	const
	{
		return m_entityType;
	}

	const std::map<ecs::AComponent::ComponentType, AComponent*>&	Entity::getComponents()	const
	{
		return m_components;
	}


	AComponent*&	Entity::operator[](ecs::AComponent::ComponentType type)
	{
		return m_components[type];
	}

	void	Entity::setOwner(ecs::ClientId owner)
	{
		m_owner = owner;
	}

	void	Entity::setEntityType(ecs::Entity::EntityType entityType)
	{
		m_entityType = entityType;
	}

	void	Entity::addComponent(ecs::AComponent::ComponentType componentType, ecs::AComponent* component)
	{
		m_components.insert(std::pair<ecs::AComponent::ComponentType, ecs::AComponent*>(componentType, component));
	}
}

std::ostream&	operator<<(std::ostream& os, const ecs::Entity& entity)
{
	auto&	components = entity.getComponents();

	os << "Entity {owner = " << entity.getOwner() << ", components = [";
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		os << *(it->second) << (std::next(it) != components.end() ? ", " : "");
	}
	os << "]}";
	return os;
}


RakNet::BitStream&	RakNet::operator<<(RakNet::BitStream& out, ecs::Entity& in)
{
	auto&	components = in.getComponents();

	out.Write(in.getOwner());
	out.Write(in.getEntityType());
	out.Write(components.size());
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		it->second->serialize(out);
	}
	return out;
}

RakNet::BitStream&	RakNet::operator>>(RakNet::BitStream& in, ecs::Entity& out)
{
	ecs::ClientId			owner			= 0;
	ecs::Entity::EntityType	entityType		= ecs::Entity::EntityType::NOTHING;
	std::size_t				componentsNb	= 0;

	in.Read(owner);
	in.Read(entityType);
	in.Read(componentsNb);
	out.setOwner(owner);
	out.setEntityType(entityType);
	for (std::size_t i = 0; i < componentsNb; ++i)
	{
		ecs::AComponent::ComponentType	componentType	= ecs::AComponent::ComponentType::COMPONENT_COUNT;
		ecs::AScene::SceneType			sceneType		= ecs::AScene::SceneType::SCENE_COUNT;
		ecs::AComponent					*component		= nullptr;

		in.Read(componentType);
		switch (componentType)
		{
		case ecs::AComponent::ComponentType::ARMOR:
			component = new ecs::Armor();
			break;
		case ecs::AComponent::ComponentType::CAMERA:
			std::logic_error("Deserialization of component type CAMERA not implemented"); // TODO: right?
			break;
		case ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER:
			component = new ecs::GameEventReceiver();
			break;
		case ecs::AComponent::ComponentType::LIFE:
			component = new ecs::Life(ecs::AComponent::ComponentType::LIFE);
			break;
		case ecs::AComponent::ComponentType::MOVEMENT:
			component = new ecs::Movement();
			break;
		case ecs::AComponent::ComponentType::PLAYER_INFOS:
			component = new ecs::PlayerInfos();
			break;
		case ecs::AComponent::ComponentType::POSITION:
			component = new ecs::Position();
			break;
		case ecs::AComponent::ComponentType::SCENE:
			in.Read(sceneType);
			switch (sceneType)
			{
			case ecs::AScene::SceneType::MESH:
				component = new ecs::SceneMesh();
				break;
			case ecs::AScene::SceneType::ANIMATED_MESH:
				component = new ecs::SceneAnimatedMesh();
				break;
			case ecs::AScene::SceneType::BILLBOARD:
				component = new ecs::SceneBillboard();
				break;
			default:
				throw std::logic_error("Bad scene type " + std::to_string(static_cast<int>(sceneType)));
				break;
			}
			break;
		case ecs::AComponent::ComponentType::SPELL:
			component = new ecs::Spell();
			break;
		case ecs::AComponent::ComponentType::SPELL_MANAGER:
			component = new ecs::SpellManager();
			break;
		case ecs::AComponent::ComponentType::TEAM:
			component = new ecs::Team();
			break;
		case ecs::AComponent::ComponentType::WEAPON:
			component = new ecs::Weapon();
			break;
		case ecs::AComponent::ComponentType::WEAPON_MANAGER:
			component = new ecs::WeaponManager();
			break;
		default:
			throw std::logic_error("Bad component type " + std::to_string(static_cast<int>(componentType)));
			break;
		}
		component->deserialize(in);
		out.addComponent(componentType, component);
	}
	return in;
}
