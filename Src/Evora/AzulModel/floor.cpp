#include "floor.h"
namespace model
{
	const std::vector<int> floor::FLOOR_SCORE = { -1, -1, -2, -2, -2, -3, -3 };
	void floor::add_tiles(tile type, int count, lid& lid)
	{
		for (int i = 0; i < count; i++)
		{
			if(m_tiles.size() == FLOOR_SIZE)
			{
				lid.add_tiles(type, count - i);
				break;
			}
			m_tiles.emplace_back(type);
		}
	}

	bool floor::empty(lid& lid)
	{
		bool res = false;
		for (auto && tile : m_tiles)
		{
			if(tile == tile::starter)
			{
				res = true;
				continue;
			}
			lid.add_tile(tile);
		}
		m_tiles.clear();
		return res;
	}

	int floor::score() const
	{
		int res = 0;
		for (int i = 0; i < m_tiles.size(); ++i)
		{
			res += FLOOR_SCORE[i];
		}
		return res;
	}
}
