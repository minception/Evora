#pragma once

#include<array>

#include "Tile.h"

namespace engine {
	class Lid
	{
	private:
		static const uint32_t MAX_TILES = 100;
		std::array<Tile, MAX_TILES> m_tiles;
	public:
		Lid();
		~Lid();
	};
}
