#pragma once
#include <vector>
#include "tile.h"

namespace model
{
	class bag
	{
		static const int TILES;
		std::vector<tile> m_tiles;
		void generate_tiles(int count, tile color);
	public:
		bag();
	};
}
