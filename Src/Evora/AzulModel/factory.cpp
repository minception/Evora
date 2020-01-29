#include "factory.h"

namespace model
{
	int factory::pick_color(tile color)
	{
		int res(0);
		std::remove_if(m_tiles.begin(), m_tiles.end(), [color, &res](tile t)
		{
			if (t == color)
			{
				++res;
				return true;
			}
			return false;
		});
		return res;
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

	int factory::add_to_center(center& center)
	{
		int res = m_tiles.size();
		for(auto&& tile: m_tiles)
		{
			center.add_tile(tile);
		}
		m_tiles.clear();
		return res;
	}
}
