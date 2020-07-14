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
		generate_tiles(TILES / COLORS, tile::red);
		generate_tiles(TILES / COLORS, tile::yellow);
		generate_tiles(TILES / COLORS, tile::blue);
		generate_tiles(TILES / COLORS, tile::black);
		generate_tiles(TILES / COLORS, tile::white);
	}

	void bag::shuffle(std::shared_ptr<std::mt19937> rng)
	{
		std::shuffle(m_tiles.begin(), m_tiles.end(), *rng);
	}

	bool bag::draw_tile(tile& out)
	{
		if (m_tiles.empty()) return false;
		out = m_tiles.back();
		m_tiles.pop_back();
		return true;
	}

	bool bag::refill(lid& lid)
	{
		std::vector<tile> to_refill;
		if(lid.get_tiles(to_refill))
		{
			m_tiles.insert(m_tiles.end(), to_refill.begin(), to_refill.end());
			return true;
		}
		return false;
	}

	bool bag::empty()
	{
		return m_tiles.empty();
	}

	void bag::return_tile(tile tile)
	{
		m_tiles.push_back(tile);
	}

	void bag::remove_tile(tile tile)
	{
		for(int i = 0; i < m_tiles.size(); ++i)
		{
			if(m_tiles[i] == tile)
			{
				m_tiles.erase(m_tiles.begin() + i);
				return;
			}
		}
	}
}
