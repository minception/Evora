#include "Factory.h"

namespace engine {
	factory::factory()
	{
		for (size_t i = 0; i < MAX_TILES; ++i)
		{
			m_tiles.emplace_back(type::empty);
		}
	}

	bool factory::fill(bag bag)
	{
		tile temp(type::empty);
		for (size_t i = 0; i < m_tiles.size(); i++)  // NOLINT(modernize-loop-convert)
		{
			if(m_tiles[i].GetType() != type::empty)
			{
				continue;
			}
			if(bag.getTile(temp))
			{
				m_tiles[i] = temp;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}
