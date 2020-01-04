#include "board.h"

namespace model
{
	board::board()
	{
		for (int i = 0; i < COLORS; i++)
		{
			m_pattern_lines.emplace_back(i + 1);
		}
	}

	bool board::can_put_color(int line, tile color)
	{
		return m_wall.can_add_color(line, color) && m_pattern_lines[line].can_put_color(color);
	}

	bool board::add_tiles(int line, int count, tile color, lid& lid, bool first_center)
	{
		if (!can_put_color(line, color)) return false;
		
		return m_pattern_lines[line].add_tiles(count, color, m_floor, lid);
	}

	bool board::tile_wall(lid& lid)
	{
		bool res = false;
		int line(0);
		for (auto && pattern_line : m_pattern_lines)
		{
			m_score += m_wall.tile(pattern_line, line, lid);
			if (m_wall.full_line(line)) res = true;
			++line;
		}
		return res;
	}

	int board::get_score() const
	{
		return m_score;
	}
}
