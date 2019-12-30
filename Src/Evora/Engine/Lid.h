#pragma once

#include<vector>

#include "Tile.h"

namespace engine {
	using lid_iterator = std::vector<tile>::const_iterator;
	class lid
	{
	private:
		static const uint32_t MAX_TILES = 100;
		std::vector<tile> m_tiles;
	public:
		lid();

		bool is_empty() const { return m_tiles.empty(); }
		bool get_tile(tile& out);
	};
}
