#pragma once

#include <array>

#include "Tile.h"
#include "Lid.h"

namespace engine {
	class Bag
	{
	private:
		static const uint32_t SIZE = 100;
		std::array<Tile, SIZE> m_tiles;
	public:
		Bag(int numberOfTiles = SIZE);
		~Bag();
	};
}
