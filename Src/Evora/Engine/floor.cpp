#include "floor.h"

namespace model
{
	const std::vector<int> floor::FLOOR_SCORE = {-1, -1, -2, -2, -2, -3, -3};

	std::vector<tile>::const_iterator floor::begin() const
	{
		return m_tiles.cbegin();
	}

	std::vector<tile>::const_iterator floor::end() const
	{
		return m_tiles.cend();
	}

	void floor::add_tile(tile color)
	{
		m_tiles.push_back(color);
	}

	bool floor::full()
	{
		return m_tiles.size() == FLOOR_SIZE;
	}

	int floor::score()
	{
		int score = 0;
		for (int i = 0; i < m_tiles.size(); ++i)
		{
			score += FLOOR_SCORE[i];
		}
		return score;
	}

	int floor::score(int tiles)
	{

		int score = 0;
		for (int i = m_tiles.size(); i < m_tiles.size() + tiles; ++i)
		{
			if (i == FLOOR_SIZE) break;
			score += FLOOR_SCORE[i];
		}
		return score;
	}

	int floor::move_to_lid(lid& lid)
	{
		int size = static_cast<int>(m_tiles.size());
		for (auto tile : m_tiles)
		{
			lid.add_tile(tile);
		}
		m_tiles.clear();
		return size;
	}

	bool floor::handle_starter_tile()
	{
		if (!m_tiles.empty() && m_tiles[0] == tile::starter)
		{
			m_tiles.erase(m_tiles.begin());
			return true;
		}
		return false;
	}

	void floor::remove_tiles(int count)
	{
		m_tiles.erase(m_tiles.end() - count, m_tiles.end());
	}

	void floor::take_starter_tile()
	{
		if (m_tiles.size() > 0 && m_tiles[0] == tile::starter)
		{
			m_tiles.erase(m_tiles.begin());
		}
	}

	void floor::add_starter()
	{
		m_tiles.insert(m_tiles.begin(), tile::starter);
	}
}
