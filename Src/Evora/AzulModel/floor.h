#pragma once
#include <vector>
#include "tile.h"
#include "lid.h"

namespace model
{
	class floor
	{
		static const int FLOOR_SIZE = 7;
		static const std::vector<int> FLOOR_SCORE;
		std::vector<tile> m_tiles;
	public:
		void add_tiles(tile type, int count, lid& lid);
		bool empty(lid& lid);
	};
	
}
