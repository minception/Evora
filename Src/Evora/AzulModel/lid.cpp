#include "lid.h"

namespace model
{
	void lid::add_tiles(tile type, int count)
	{
		_ASSERT(type == tile::starter, "starter tile got into lid");
		for (int i = 0; i < count; i++)
		{
			m_tiles.emplace_back(type);
		}
	}

	void lid::add_tile(tile type)
	{
		m_tiles.emplace_back(type);
	}
}
