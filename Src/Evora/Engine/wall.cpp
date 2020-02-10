#include "wall.h"

namespace model
{
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

	void wall::add_tile(int pattern_line_index, tile tile)
	{
		int row = ((int)tile + pattern_line_index) % COLORS;
		m_tiles[pattern_line_index][row] = tile;
	}

	int wall::score_tile(int pattern_line_index, tile tile)
	{
		int row = ((int)tile + pattern_line_index) % COLORS;
		return score(pattern_line_index, row);
	}
}
