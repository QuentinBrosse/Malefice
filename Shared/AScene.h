#pragma once

#include "AComponent.h"
#include "Position.h"

#include <irrlicht.h>

namespace ecs
{
	class MALEFICE_DLL_EXPORT AScene : public AComponent
	{
	public:
		AScene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags);
		virtual ~AScene() = 0;

		std::string				getNameTexture()	const;
		std::string				getNameMesh()		const;
		int						getPickableFlags()	const;
		irr::video::SMaterial*	getMaterial()		const;

		void					setNameTexture(const std::string& newNameTexture);
		void					setNameMesh(const std::string& newNameMesh);
		void					setPickableFlags(int newPickableFlags);
		void					setMaterial(irr::video::SMaterial* newMaterial);
		virtual	void			setPosition(const Position& newPosition) = 0;   // Will set m_node's Position and Rotation


		virtual void	dump(std::ostream& os)	const;


	protected:
		const std::string			MEDIA_PATH;
		std::string					m_nameTexture;
		std::string					m_nameMesh;
		int							m_pickableFlags;
		irr::IrrlichtDevice*		m_device;
		irr::video::SMaterial*		m_material;
		irr::scene::ISceneManager*	m_smgr;
		irr::video::IVideoDriver*	m_driver;
	};
}
