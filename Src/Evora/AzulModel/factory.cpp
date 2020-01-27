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

	int factory::offer(tile color)
	{
		int res(0);
		for (auto && tile : m_tiles)
		{
			if (tile == color) ++res;
		}
		return res;
	}

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

	bool factory::empty()
	{
		return m_tiles.empty();
	}

	std::vector<tile>::const_iterator factory::begin() const
	{
		return m_tiles.cbegin();
	}

	std::vector<tile>::const_iterator factory::end() const
	{
		return m_tiles.cend();
	}
}
