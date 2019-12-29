#pragma once

#include<vector>

#include "Tile.h"

namespace engine {
	class factory
	{
	private:
		static const uint32_t MAX_TILES = 4;
		std::vector<tile> m_tiles;
	public:
		factory();
	};
}
