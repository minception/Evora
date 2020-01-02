#include "bag.h"
namespace model
{
	void bag::generate_tiles(int count, tile color)
	{
		for (int i = 0; i < count; i++)
		{
			m_tiles.emplace_back(color);
		}
	}

	bag::bag()
	{
		generate_tiles(TILES / COLORS, red);
		generate_tiles(TILES / COLORS, yellow);
		generate_tiles(TILES / COLORS, blue);
		generate_tiles(TILES / COLORS, black);
		generate_tiles(TILES / COLORS, white);
	}
}
