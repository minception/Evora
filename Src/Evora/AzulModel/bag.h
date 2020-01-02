#pragma once
#include <vector>
#include <random>

#include "tile.h"

namespace model
{
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
	};
}
