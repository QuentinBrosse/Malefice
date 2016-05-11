#include "SceneMesh.h"

namespace ecs
{

	SceneMesh::SceneMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const std::string& namePK3): AScene(device, newNameTexture, newNameMesh, newPickableFlags),
		m_node(nullptr)
	{
		irr::scene::IAnimatedMesh*		mesh;
		
		if (namePK3 != "")
		{
			m_device->getFileSystem()->addFileArchive((MEDIA_PATH + namePK3).c_str());
			std::cout << (newNameMesh) << std::endl;
			mesh = m_smgr->getMesh(newNameMesh.c_str());
		}
		else
		{
			//TODO: constructor without decompression
			std::cerr << "No Compression !" << std::endl;
		}
		if (mesh)
			m_node = m_smgr->addOctreeSceneNode(mesh->getMesh(0), 0, newPickableFlags);
		else
			std::cerr << "Error constructor SceneMesh : mesh NULL !!" << std::endl;
		if (m_node)
			m_node->setTriangleSelector(m_smgr->createOctreeTriangleSelector(m_node->getMesh(), m_node, 128));
		else
			std::cerr << "Error constructor SceneMesh : m_node NULL !!" << std::endl;
	}

	SceneMesh::~SceneMesh()
	{
	}

	void SceneMesh::setPosition(const Position& newPosition)
	{
		m_node->setPosition(newPosition.getVectorPosition());
		m_node->setRotation(newPosition.getVectorRotation());
	}

}