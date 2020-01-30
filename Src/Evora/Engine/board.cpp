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

	void board::set_starter_tile(bool cond)
	{
		m_has_starter_tile = cond;
	}
}
