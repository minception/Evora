#pragma once
#include <vector>
#include "floor.h"
#include "pattern_line.h"
#include "wall.h"
#include <map>

namespace model
{
	class board
	{
		bool starts;
		int m_score{0};
		std::vector<pattern_line> m_pattern_lines;
		wall m_wall;
		floor m_floor;
	public:
		board();
	};
}
