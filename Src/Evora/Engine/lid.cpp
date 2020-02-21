#include "lid.h"

namespace model
{
	void lid::add_tiles(int count, tile color)
	{
		for (int i = 0; i < count; i++)
		{
			m_tiles.emplace_back(color);
		}
	}

	void lid::add_tile(tile type)
	{
		m_tiles.emplace_back(type);
	}

	bool lid::get_tiles(std::vector<tile>& out)
	{
		if (empty()) return false;
		out = m_tiles;
		m_tiles.clear();
		return true;
	}

	bool lid::empty() const
	{
		return m_tiles.empty();
	}

	std::vector<tile> lid::get_state()
	{
		std::vector<tile> res;
		// return std::copy(m_tiles.begin(), m_tiles.end(), res);
		return res;
	}
}
