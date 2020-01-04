#include "factory.h"

namespace model
{
	bool factory::fill(bag& bag)
	{
		tile temp;
		for (int i = m_tiles.size(); i < TILES; i++)
		{
			if (!bag.draw_tile(temp)) return false;
			m_tiles.emplace_back(temp);
		}
		return true;
	}

	int factory::offer(tile color)
	{
		int res(0);
		for (auto && tile : m_tiles)
		{
			if (tile == color) ++res;
		}
		return res;
	}

	void factory::pick_color(tile color, center& center)
	{
		for (auto && tile : m_tiles)
		{
			if (tile != color) center.add_tile(tile);
		}
		m_tiles.clear();
	}

	bool factory::empty()
	{
		return m_tiles.empty();
	}
}
