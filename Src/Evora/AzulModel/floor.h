#pragma once

#include <vector>

#include "lid.h"
#include "tile.h"

namespace model
{
	class floor
	{
		static const int FLOOR_SIZE = 7;
		static const std::vector<int> FLOOR_SCORE;
		std::vector<tile> m_tiles;
		
	public:
		int add_tiles(int count, tile color);
		bool empty(lid& lid);
		bool is_full() const { return m_tiles.size() == FLOOR_SIZE; }
		int score() const;

		// iterator methods for display purposes
		std::vector<tile>::const_iterator begin() const;
		std::vector<tile>::const_iterator end() const;
	};
}
