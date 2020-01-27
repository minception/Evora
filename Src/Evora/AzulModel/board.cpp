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

	std::tuple<int, int> board::add_tiles(int line, int count, tile color)
	{		
		return m_pattern_lines[line].add_tiles(count, color);
	}

	bool board::tile_wall(lid& lid)
	{
		bool res = false;
		int line(0);
		for (auto && pattern_line : m_pattern_lines)
		{
			m_score += m_wall.tile_wall(pattern_line, line, lid);
			if (m_wall.full_line(line)) res = true;
			++line;
		}
		return res;
	}

	int board::get_score() const
	{
		return m_score;
	}

	std::vector<std::vector<tile>>::const_iterator board::wall_begin() const
	{
		return m_wall.begin();
	}

	std::vector<std::vector<tile>>::const_iterator board::wall_end() const
	{
		return m_wall.end();
	}

	std::vector<pattern_line>::const_iterator board::pattern_lines_begin() const
	{
		return m_pattern_lines.cbegin();
	}

	std::vector<pattern_line>::const_iterator board::pattern_lines_end() const
	{
		return m_pattern_lines.cend();
	}

	std::vector<tile>::const_iterator board::floor_begin() const
	{
		return m_floor.begin();
	}

	std::vector<tile>::const_iterator board::floor_end() const
	{
		return m_floor.end();
	}

	int board::add_to_floor(int count, tile color)
	{
		return m_floor.add_tiles(count, color);
	}
}
