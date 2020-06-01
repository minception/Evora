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
		
		std::vector<int> get_tile_indices(tile color);
		bool pick_color_tile(tile color);
		bool pick_starter_tile();
		bool empty();
		std::vector<tile> get_colors();
		void return_tiles(tile color, int count, std::vector<int>& is);
		void add_starter_tile();
		void remove_tiles(int count);
		tile pop_tile();
		std::vector<std::tuple<tile, int>> get_colors_count();
		int tile_count(tile color);
	};
}
