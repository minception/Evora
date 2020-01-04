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
		int tile_wall(int line);
	public:
		board();
		bool can_put_color(int line, tile color);
		bool add_tiles(int line, int count, tile color, lid& lid, bool first_center = false);
		bool tile_wall(lid& lid);
		int get_score() const;
	};
}
