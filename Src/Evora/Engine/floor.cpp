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
}
