#include "wall.h"

namespace model
{

	const std::vector<std::map<tile, int>> wall::WALL_COLORS =
	{
		{{tile::blue, 0}, {tile::yellow, 1}, {tile::red, 2}, {tile::black, 3}, {tile::white, 4}},
		{{tile::white, 0}, {tile::blue, 1}, {tile::yellow, 2}, {tile::red, 3}, {tile::black, 4}},
		{{tile::black, 0}, {tile::white, 1}, {tile::blue, 2}, {tile::yellow, 3}, {tile::red, 4}},
		{{tile::red, 0}, {tile::black, 1}, {tile::white, 2}, {tile::blue, 3}, {tile::yellow, 4}},
		{{tile::yellow, 0}, {tile::red, 1}, {tile::black, 2}, {tile::white, 3}, {tile::blue, 4}}
	};

	int wall::score(int x, int y)
	{
		const int h_score = horizontal_score(x, y);
		const int v_score = vertical_score(x, y);
		if (h_score == 1) return v_score;
		if (v_score == 1) return h_score;
		return v_score + h_score;
	}

	int wall::horizontal_score(int x, int y)
	{
		long first = x;
		long last = x;
		while (first > 0 && m_tiles[y][first - 1l] != tile::empty) first--;
		while (last < COLORS - 1 && m_tiles[y][last + 1l] != tile::empty) last++;
		return last - first + 1;
	}

	int wall::vertical_score(int x, int y)
	{
		long first = y;
		long last = y;
		while (first > 0 && m_tiles[first - 1l][x] != tile::empty) first--;
		while (last < COLORS - 1 && m_tiles[last + 1l][x] != tile::empty) last++;
		return last - first + 1;
	}

	wall::wall()
	{
		for (int i = 0; i < COLORS; i++)
		{
			m_tiles.emplace_back();
			for (int j = 0; j < COLORS; j++)
			{
				m_tiles[i].emplace_back(tile::empty);
			}
		}
	}

	bool wall::can_add_color(int line, model::tile color)
	{
		return m_tiles[line][WALL_COLORS[line].at(color)] == tile::empty;
	}

	int wall::tile_wall(pattern_line& pattern_line, int line, lid& lid)
	{
		int x = WALL_COLORS[line].at(pattern_line.get_color());
		m_tiles[line][x] = pattern_line.get_color();
		pattern_line.clear(lid);
		return score(x, line);
	}

	int wall::count_finished_lines()
	{
		int result(0);
		for (int i = 0; i < COLORS; i++)
		{
			for (int j = 0; j < COLORS; j++)
			{
				if (m_tiles[i][j] == tile::empty)
				{
					break;
				}
				if (j == COLORS - 1) ++result;
			}
		}
		return result;
	}

	int wall::count_finished_columns()
	{
		int result(0);
		for (int i = 0; i < COLORS; i++)
		{
			for (int j = 0; j < COLORS; j++)
			{
				if (m_tiles[j][i] == tile::empty)
				{
					break;
				}
				if (j == COLORS - 1) ++result;
			}
		}
		return result;
	}

	int wall::count_finished_colors()
	{
		std::map<model::tile, int> colorcount;
		for (int i = 0; i < COLORS; i++)
		{
			for (int j = 0; j < COLORS; j++)
			{
				if (m_tiles[i][j] != tile::empty)
				{
					++colorcount.at(m_tiles[i][j]);
				}
			}
		}
		int result(0);
		for (auto && color : colorcount)
		{
			if (color.second == COLORS) ++result;
		}
		return result;
	}

	int wall::final_score()
	{
		return count_finished_lines() * 2 + count_finished_columns() * 7 + count_finished_colors() * 10;
		
	}

	bool wall::full_line(int line)
	{
		for (int i = 0; i < COLORS; ++i)
		{
			if (m_tiles[line][i] == tile::empty) return false;
		}
		return true;
	}

	std::vector<std::vector<tile>>::const_iterator wall::begin() const
	{
		return m_tiles.cbegin();
	}

	std::vector<std::vector<tile>>::const_iterator wall::end() const
	{
		return m_tiles.cend();
	}
}
