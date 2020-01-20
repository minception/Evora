#include "lid.h"

namespace model
{
	void lid::add_tiles(tile type, int count)
	{
		// _ASSERT(type == tile_wall::starter, "starter tile_wall got into lid");
		for (int i = 0; i < count; i++)
		{
			m_tiles.emplace_back(type);
		}
	}

	void lid::add_tile(tile type)
	{
		m_tiles.emplace_back(type);
	}

	bool lid::get_tiles(std::vector<tile>& out)
	{
		if (empty()) return false;
		std::copy(m_tiles.begin(), m_tiles.end(), out.begin());
		m_tiles.clear();
		return true;
	}

	bool lid::empty() const
	{
		return m_tiles.empty();
	}
}
