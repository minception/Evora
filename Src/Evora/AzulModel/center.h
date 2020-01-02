#pragma once
#include <vector>
#include "tile.h"

namespace model
{
	class center
	{
		std::vector<tile> m_tiles;
	public:
		void add_tile(tile type);
	};
}
