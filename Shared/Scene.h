#pragma once

#include "AComponent.h"
#include <irrlicht.h>

namespace ecs
{
	class Scene : public AComponent
	{
	public:
		Scene(irr::scene::ISceneManager* newSmgr, irr::video::IVideoDriver* newDriver, const std::string& newNameTexture, std::string& newNameMesh, int newPickableFlags);
		~Scene();

	public:
		irr::scene::ISceneManager* getSmgr() const;
		irr::video::IVideoDriver* getDriver() const;
		std::string getNameTexture() const;
		std::string getNameMesh() const;
		int getPickableFlags() const;
		void setSmgr(irr::scene::ISceneManager* newSmgr);
		void setDriver(irr::video::IVideoDriver* newDriver);
		void setNameTexture(const std::string& newNameTexture);
		void setNameMesh(const std::string& newNameMesh);
		void setPickableFlags(int newPickableFlags);

	public:
		irr::scene::IAnimatedMeshSceneNode* getNode()const;
		irr::video::SMaterial* getMaterial()const;
		void setNode(irr::scene::IAnimatedMeshSceneNode* newNode);
		void setMaterial(irr::video::SMaterial* newMaterial);

	private:
		irr::scene::ISceneManager* m_smgr;
		irr::video::IVideoDriver* m_driver;
		std::string m_nameTexture;
		std::string m_nameMesh;
		int m_pickableFlags;

	private:
		irr::scene::IAnimatedMeshSceneNode* m_node;
		irr::video::SMaterial* m_material;
	};
}