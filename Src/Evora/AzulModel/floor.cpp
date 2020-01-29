#include "floor.h"
namespace model
{
	const std::vector<int> floor::FLOOR_SCORE = { -1, -1, -2, -2, -2, -3, -3 };
	int floor::add_tiles(int count, tile color)
	{
		for (int i = 0; i < count; i++)
		{
			if(m_tiles.size() == FLOOR_SIZE)
			{
				return count - i;
			}
			m_tiles.emplace_back(color);
		}
		return 0;
	}
	
	std::vector<tile>::const_iterator floor::begin() const
	{
		return m_tiles.cbegin();
	}

	std::vector<tile>::const_iterator floor::end() const
	{
		return m_tiles.cend();
	}
}
