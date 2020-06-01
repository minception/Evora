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
		if (!m_tiles.empty() && m_tiles[0] == tile::starter)
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

	void center::return_tiles(tile color, int count, std::vector<int>& is)
	{
		for (int i = 0; i < count; ++i)
		{
			int position = is.front();
			is.erase(is.begin());
			m_tiles.insert(m_tiles.begin() + position, color);
		}
	}

	void center::add_starter_tile()
	{
		m_tiles.insert(m_tiles.begin(), tile::starter);
	}

	void center::remove_tiles(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			m_tiles.pop_back();
		}
	}

	tile center::pop_tile()
	{
		tile color = m_tiles.back();
		m_tiles.pop_back();
		return color;
	}

	std::vector<std::tuple<tile, int>> center::get_colors_count()
	{
		std::vector<std::tuple<tile, int>> res;
		for (auto&& tile : m_tiles)
		{
			if (tile == tile::starter) continue;
			bool found = false;
			for(auto&& cq : res)
			{
				if(std::get<0>(cq) == tile)
				{
					std::get<1>(cq)++;
					found = true;
					break;
				}
			}
			if(!found)
			{
				res.emplace_back(tile, 1);
			}
		}
		return res;
	}

	int center::tile_count(tile color)
	{
		int res(0);
		std::for_each(m_tiles.begin(), m_tiles.end(), [&res, color](auto tile) {if (tile == color) { ++res; }});
		return res;
	}
}
