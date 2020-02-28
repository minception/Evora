#include "center.h"
#include <algorithm>

namespace model
{
	void center::add_tile(tile type)
	{
		m_tiles.emplace_back(type);
	}

	std::vector<tile>::const_iterator center::begin() const
	{
		return m_tiles.cbegin();
	}

	std::vector<tile>::const_iterator center::end() const
	{
		return m_tiles.cend();
	}

	std::vector<int> center::get_tile_indices(tile color)
	{
		std::vector<int> res;
		for (int i = 0; i < m_tiles.size(); ++i)
		{
			if(m_tiles[i]== color)
			{
				res.push_back(i);
			}
		}
		return res;
	}

	bool center::pick_color_tile(tile color)
	{
		for (int i = 0; i < m_tiles.size(); ++i)
		{
			if (m_tiles[i] == color)
			{
				m_tiles.erase(m_tiles.begin() + i);
				return true;
			}
		}
		return false;
	}

	bool center::pick_starter_tile()
	{
		if (m_tiles[0] == tile::starter)
		{
			m_tiles.erase(m_tiles.begin());
			return true;
		}
		return false;
	}

	bool center::empty()
	{
		return m_tiles.empty();
	}

	std::vector<tile> center::get_colors()
	{
		std::vector<tile> res;
		for (auto&& tile : m_tiles)
		{
			if (tile == tile::starter) continue;
			if (std::find(res.begin(), res.end(), tile) == res.end()) res.push_back(tile);
		}
		return res;
	}
}
