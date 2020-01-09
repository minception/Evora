#pragma once

#include <vector>
#include "tile.h"

namespace model
{
	class lid
	{
		std::vector<tile> m_tiles;
	public:
		void add_tiles(tile type, int count);
		void add_tile(tile type);
	};
}
