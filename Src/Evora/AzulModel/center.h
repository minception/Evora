#pragma once
#include <vector>
#include "tile.h"

namespace model
{
	class center
	{
		std::vector<tile> m_tiles;
		bool first_pick = true;
	public:
		void add_tile(tile type);
		bool empty() const;
		int offer(tile color, bool& first);
		void pick_color(tile color);
	};
}
