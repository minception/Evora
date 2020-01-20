#pragma once

#include <random>
#include <vector>

#include "tile.h"
#include "lid.h"

namespace model
{
	class lid;

	class bag
	{
		static const int TILES = 100;
		std::vector<tile> m_tiles;
		std::mt19937 m_rng;
		void generate_tiles(int count, tile color);
	public:
		bag();
		void shuffle();
		bool draw_tile(tile& out);
		bool refill(lid& lid);
	};
}
