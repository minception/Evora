#pragma once

#include<vector>

#include "Tile.h"

namespace engine {
	class lid
	{
	private:
		static const uint32_t MAX_TILES = 100;
		std::vector<tile> m_tiles;
	public:
		lid();
	};
}
