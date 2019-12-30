#include "Factory.h"

namespace engine {
	factory::factory()
	{
		for (size_t i = 0; i < MAX_TILES; ++i)
		{
			m_tiles.emplace_back(type::empty);
		}
	}

	bool factory::fill(bag& bag)
	{
		tile temp(type::empty);
		for (size_t i = 0; i < m_tiles.size(); i++)  // NOLINT(modernize-loop-convert)
		{
			if(m_tiles[i].get_type() != type::empty)
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

	int factory::get_tiles_of_color(type color)
	{
		int res = 0;
		for (auto && tile : m_tiles)
		{
			if (tile.get_type() == color)
			{
				tile.set_type(type::empty);
				++res;
			}
		}
		return res;
	}

	void factory::empty_to_center(center& center)
	{
		for (auto && tile : m_tiles)
		{
			if (tile.is_empty()) continue;
			center.add_tile(tile.get_type());
			tile.set_type(type::empty); 
		}
	}

	factory_iterator factory::begin() const
	{
		return m_tiles.cbegin();
	}

	factory_iterator factory::end() const
	{
		return m_tiles.cend();
	}
}
