#pragma once
#include "tile.h"
#include "pattern_line.h"
#include "lid.h"
#include <map>
#include <vector>

namespace model
{
	class wall
	{
		static const std::vector < std::map<tile, int>> WALL_COLORS;
		std::vector<std::vector<tile>> m_tiles;
		int score(int x, int y);
		int horizontal_score(int x, int y);
		int vertical_score(int x, int y);
		int count_finished_lines();
		int count_finished_columns();
		int count_finished_colors();
		
	public:
		wall();
		bool can_add_color(int line, tile color);
		int tile(pattern_line& pattern_line, int line, lid& lid);
		int final_score();
	};
}
