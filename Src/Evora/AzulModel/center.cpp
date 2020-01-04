#include "center.h"
#include <algorithm>

namespace model
{
	void center::add_tile(tile type)
	{
		m_tiles.emplace_back(type);
	}

	bool center::empty() const
	{
		return m_tiles.empty();
	}

	int center::offer(tile color, bool& first)
	{
		int res = 0;
		for (auto && tile : m_tiles)
		{
			if (tile == color) ++res;
		}
		first = first_pick;
		return res;
	}
	void center::pick_color(tile color)
	{
		auto to_remove = std::find(m_tiles.begin(), m_tiles.end(), color);
		while(to_remove != m_tiles.end())
		{
			m_tiles.erase(to_remove);
			to_remove = std::find(m_tiles.begin(), m_tiles.end(), color);
		}
		if(first_pick)
		{
			first_pick = false;
		}
	}
}
