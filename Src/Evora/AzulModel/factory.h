#pragma once
#include <vector>
#include "tile.h"
#include "bag.h"
#include "center.h"

namespace model
{
	class factory
	{
		static const int TILES = 4;
		std::vector<tile> m_tiles;
	public:
		bool fill(bag& bag);
		int offer(tile color);
		int pick_color(tile color, center& center);
	};
}
