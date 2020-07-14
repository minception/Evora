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
		// iterator methods for display purposes
		std::vector<tile>::const_iterator begin() const;
		std::vector<tile>::const_iterator end() const;
		void add_tile(tile color);
		bool full();
		int score();
		int score(int tiles);
		int move_to_lid(lid& lid);
		bool handle_starter_tile();
		void remove_tiles(int count);
		void take_starter_tile();
		void add_starter();
	};
}
