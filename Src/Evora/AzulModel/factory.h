#pragma once

#include <algorithm>
#include <vector>

#include "bag.h"
#include "center.h"
#include "tile.h"

namespace model
{
	class factory
	{
		static const int TILES = 4;
		std::vector<tile> m_tiles;
		
	public:
		bool fill(bag& bag);
		int offer(tile color);
		int pick_color(tile color);
		std::vector<tile> get_colors();
		bool empty();

		// iterator methods for display purposes
		std::vector<tile>::const_iterator begin() const;
		std::vector<tile>::const_iterator end() const;
	};
}
