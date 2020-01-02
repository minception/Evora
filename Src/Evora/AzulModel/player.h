#pragma once
#include <vector>
#include "tile.h"

namespace model
{
	class player
	{
		int m_score;
		std::vector<std::vector<tile>> m_pattern_lines;
		std::vector<std::vector<tile>> m_wall;
		std::vector<tile> m_floor;
	public:
	
	};
}
