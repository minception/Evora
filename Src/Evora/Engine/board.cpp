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
		if(!m_wall.empty(pattern_line_index, tile))
		{
			return false;
		}
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
		int score = m_wall.score_tile(pattern_line_index, tile);
		m_score += score;
		return score;
	}

	std::vector<int> board::get_score_indices(int pattern_line_index, tile tile)
	{
		return m_wall.get_score_indices(pattern_line_index, tile);
	}

	int board::score_floor()
	{
		int score = m_floor.score();
		// score cannot drop below 0
		if(m_score + score < 0)
		{
			score = -m_score;
			m_score = 0;
		}
		else
		{
			m_score += score;
		}
		return score;
	}

	int board::floor_to_lid(lid& lid)
	{
		return m_floor.move_to_lid(lid);
	}

	int board::handle_floor_starter_tile()
	{
		return m_floor.handle_starter_tile();
	}

	bool board::game_finished()
	{
		return m_wall.game_finished();
	}

	int board::score_wall_color(tile tile)
	{
		return m_wall.score_color(tile);
	}

	int board::score_wall_line(int line)
	{
		return m_wall.score_line(line);
	}

	int board::score_wall_row(int row)
	{
		return m_wall.score_row(row);
	}
}
