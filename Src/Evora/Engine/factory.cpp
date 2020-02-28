#include "factory.h"

namespace model
{
	bool factory::pick_color_tile(tile color)
	{
		for (int i = 0; i < m_tiles.size(); ++i)
		{
			if(m_tiles[i] == color)
			{
				m_tiles.erase(m_tiles.begin() + i);
				return true;
			}
		}
		return false;
	}

	std::vector<tile> factory::get_colors()
	{
		std::vector<tile> res;
		for (auto&& tile : m_tiles)
		{
			if (std::find(res.begin(), res.end(), tile) == res.end()) res.push_back(tile);
		}
		return res;
	}

	std::vector<tile>::const_iterator factory::begin() const
	{
		return m_tiles.cbegin();
	}

	std::vector<tile>::const_iterator factory::end() const
	{
		return m_tiles.cend();
	}

	bool factory::empty()
	{
		return m_tiles.empty();
	}

	int factory::add_to_center(center& center)
	{
		int res = static_cast<int>(m_tiles.size());
		for(auto&& tile: m_tiles)
		{
			center.add_tile(tile);
		}
		m_tiles.clear();
		return res;
	}

	int factory::fill(bag& bag)
	{
		int added = 0;
		for(size_t i = m_tiles.size(); i < TILES; ++i)
		{
			tile temp;
			if (bag.draw_tile(temp))
			{
				m_tiles.push_back(temp);
				++added;
			}
			else
			{
				return added;
			}
		}
		return added;
	}
}
