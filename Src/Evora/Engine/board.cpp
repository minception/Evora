﻿#include "board.h"

namespace model
{
	board::board()
	{
		for (int i = 0; i < COLORS; i++)
		{
			m_pattern_lines.emplace_back(i + 1);
		}
	}

	void board::tile_wall(int pattern_line_index, tile color)
	{
		m_wall.add_tile(pattern_line_index, color);
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

	void board::add_to_floor(tile color)
	{
		m_floor.add_tile(color);
	}

	bool board::has_starter_tile()
	{
		return m_has_starter_tile;
	}

	void board::set_starter_tile(bool cond)
	{
		m_has_starter_tile = cond;
	}

	bool board::pattern_line_full(int pattern_line_index)
	{
		return m_pattern_lines[pattern_line_index].full();
	}

	void board::add_to_pattern_line(int pattern_line_index, tile tile)
	{
		m_pattern_lines[pattern_line_index].add(tile);
	}

	bool board::floor_full()
	{
		return m_floor.full();
	}

	bool board::can_add_to_pattern_line(int pattern_line_index, tile tile)
	{
		return m_pattern_lines[pattern_line_index].can_add(tile);
	}

	void board::take_starter_tile()
	{
		m_has_starter_tile = false;
	}

	void board::set_starter_player()
	{
		m_has_starter_tile = true;
	}

	tile board::pattern_line_color(int pattern_line_index)
	{
		return m_pattern_lines[pattern_line_index].get_color();
	}

	void board::clear_pattern_line(int pattern_line_index)
	{
		m_pattern_lines[pattern_line_index].clear();
	}

	int board::score_wall_tile(int pattern_line_index, tile tile)
	{
		return m_wall.score_tile(pattern_line_index, tile);
	}
}
