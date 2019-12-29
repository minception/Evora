#pragma once
#include "Tile.h"
#include <vector>

namespace engine
{
	class center
	{
	private:
		std::vector<tile> m_tiles;
		bool m_first_took = false;
		
	public:
		void add_tile(type color);
		std::tuple<bool, int> get_tiles_of_color(type color);
	};
}
