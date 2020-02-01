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
		std::vector<tile> m_tiles;
		
	public:
		static const int TILES = 4;
		
		bool pick_color_tile(tile color);
		std::vector<tile> get_colors();

		// iterator methods for display purposes
		std::vector<tile>::const_iterator begin() const;
		std::vector<tile>::const_iterator end() const;
		int add_to_center(center& center);
		int fill(bag& bag);
	};
}
