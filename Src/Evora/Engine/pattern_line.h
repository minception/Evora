#pragma once

#include "floor.h"
#include "lid.h"
#include "tile.h"
#include <tuple>

namespace model
{
	class pattern_line
	{
		tile m_color{ tile::empty };
		int m_size;
		int m_count{ 0 };
	public:
		pattern_line(int size) :m_size(size) {}
		bool full();
		void add(tile tile);
	};
}
