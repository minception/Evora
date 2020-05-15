#pragma once

#include <vector>
#include "tile.h"

namespace model
{
	class lid
	{
		std::vector<tile> m_tiles;
	public:
		void add_tiles(int count, tile color);
		void add_tile(tile type);
		bool get_tiles(std::vector<tile>& out);
		bool empty() const;
		std::vector<tile> get_state();
		void remove_tiles(int count);
		tile take_tile();
		void set_state(std::vector<tile>& tiles);
	};
}
