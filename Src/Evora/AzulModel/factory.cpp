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
}
