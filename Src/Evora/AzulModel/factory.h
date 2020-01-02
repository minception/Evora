#pragma once
#include <vector>
#include "tile.h"
#include "bag.h"

namespace model
{
	class factory
	{
		static const int TILES = 4;
		std::vector<tile> m_tiles;
	public:
		bool fill(bag& bag);
	};
}
