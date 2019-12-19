#pragma once

#include<array>

#include "Tile.h"

namespace engine {
	class Factory
	{
	private:
		static const uint32_t MAX_TILES = 4;
		std::array<Tile, MAX_TILES> m_tiles;
	};
}
