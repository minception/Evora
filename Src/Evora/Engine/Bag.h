#pragma once

#include<random>
#include <vector>

#include "Tile.h"
#include "Lid.h"

namespace engine {
	class bag
	{
	private:
		static const uint32_t SIZE = 100;
		static const uint32_t BLUE_TILES = SIZE / 5;
		static const uint32_t RED_TILES = SIZE / 5;
		static const uint32_t YELLOW_TILES = SIZE / 5;
		static const uint32_t WHITE_TILES = SIZE / 5;
		static const uint32_t BLACK_TILES = SIZE / 5;
		std::vector<tile> m_tiles;
		std::mt19937 m_rng;
	public:
		bag(int numberOfTiles = SIZE);
		bool get_tile(type& out);
		void generateTiles();
		void shuffle();
		bool is_empty() const { return m_tiles.empty(); }
		bool refill(lid lid);
	};
}
