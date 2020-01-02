﻿#pragma once
#include <vector>
#include "tile.h"

namespace model
{
	class board
	{
		static const int FLOOR_SIZE = 7;
		int m_score{0};
		std::vector<std::vector<tile>> m_pattern_lines;
		std::vector<std::vector<tile>> m_wall;
		std::vector<tile> m_floor;
	public:
		board();
	};
}
