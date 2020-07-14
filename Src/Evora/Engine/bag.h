#pragma once

#include <random>
#include <vector>

#include "tile.h"
#include "lid.h"
#include <memory>

namespace model
{
	class lid;

	class bag
	{
		static const int TILES = 100;
		std::vector<tile> m_tiles;
		void generate_tiles(int count, tile color);
	public:
		bag();
		void shuffle(std::shared_ptr<std::mt19937> rng);
		bool draw_tile(tile& out);
		bool refill(lid& lid);
		bool empty();
		void return_tile(tile tile);
		void remove_tile(tile tile);
	};
}
