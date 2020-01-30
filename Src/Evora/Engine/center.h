#pragma once

#include <vector>

#include "tile.h"
#include <tuple>

namespace model
{
	class center
	{
		std::vector<tile> m_tiles;
		bool first_pick = true;
		
	public:
		void add_tile(tile type);
		std::tuple<int, std::vector<int>> pick_color(tile color);

		// iterator methods for display purposes
		std::vector<tile>::const_iterator begin() const;
		std::vector<tile>::const_iterator end() const;
	};
}
