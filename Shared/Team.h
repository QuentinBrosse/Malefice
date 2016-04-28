#pragma once

#include "AComponent.h"

namespace ecs
{
	class Team : public AComponent
	{
	public:
		Team(int team);
		~Team();

	public:
		void dump() const;

	public:
		int getKill() const;
		int getDeath() const;
		void setKill(int);
		void setDeath(int);

	public:
		void addDeath();
		void addKill();

	public:
		const int TEAM;

	private:
		int m_iKill;
		int m_iDeath;
	};
}
