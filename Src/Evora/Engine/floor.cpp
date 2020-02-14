#include "floor.h"

namespace model
{
	const std::vector<int> floor::FLOOR_SCORE = { -1, -1, -2, -2, -2, -3, -3 };
	
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

	int floor::move_to_lid(lid& lid)
	{
		int size = m_tiles.size();
		for (auto tile : m_tiles)
		{
			lid.add_tile(tile);
		}
		m_tiles.clear();
		return size;
	}

	int floor::handle_starter_tile()
	{
		for(int i = 0; i < m_tiles.size(); ++i)
		{
			if(m_tiles[i] == tile::starter)
			{
				m_tiles.erase(m_tiles.begin() + i);
				return i;
			}
		}
		return -1;
	}
}
