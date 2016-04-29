#pragma once

#include "AComponent.h"

namespace ecs
{
	class Position: public AComponent
	{
	public:
		Position(float x, float y, float z);
		Position(const Position& pos);
		Position& operator=(const Position& pos);
		~Position() = default;

		void set(float x, float y, float z);
		void set(const Position& pos);

		void add(float x, float y, float z);
		void add(const Position& pos);
		void sub(float x, float y, float z);
		void sub(const Position& pos);

		Position& operator+=(const Position& pos);
		Position& operator-=(const Position& pos);

		Position operator+(const Position& pos) const;
		Position operator-(const Position& pos) const;

		float getX() const;
		float getY() const;
		float getZ() const;

		void dump() const;

	private:
		float m_x;
		float m_y;
		float m_z;
	};
}