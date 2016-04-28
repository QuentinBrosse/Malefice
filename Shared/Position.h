#pragma once

#include "AComponent.h"

namespace ecs
{
	class Position: public AComponent
	{
	public:
		Position(int x, int y, int z);
		Position(const Position& pos);
		Position& operator=(const Position& pos);
		~Position() = default;

		void set(int x, int y, int z);
		void set(const Position& pos);

		void add(int x, int y, int z);
		void add(const Position& pos);
		void sub(int x, int y, int z);
		void sub(const Position& pos);

		Position& operator+=(const Position& pos);
		Position& operator-=(const Position& pos);

		Position operator+(const Position& pos) const;
		Position operator-(const Position& pos) const;

		int getX() const;
		int getY() const;
		int getZ() const;

		void dump() const;

	private:
		int m_iX;
		int m_iY;
		int m_iZ;
	};
}