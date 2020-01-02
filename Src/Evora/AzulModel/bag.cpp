#include <algorithm>

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
		std::random_device seed;
		m_rng = std::default_random_engine{ seed() };
		generate_tiles(TILES / COLORS, tile::red);
		generate_tiles(TILES / COLORS, tile::yellow);
		generate_tiles(TILES / COLORS, tile::blue);
		generate_tiles(TILES / COLORS, tile::black);
		generate_tiles(TILES / COLORS, tile::white);
	}

	void bag::shuffle()
	{
		std::shuffle(m_tiles.begin(), m_tiles.end(), m_rng);
	}

	bool bag::draw_tile(tile& out)
	{
		if (m_tiles.empty()) return false;
		out = m_tiles.back();
		m_tiles.pop_back();
	}
}
