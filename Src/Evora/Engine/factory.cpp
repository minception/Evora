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

	void factory::add_tiles(tile color, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			m_tiles.push_back(color);
		}
	}

	void factory::add_from_center(center& center, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			tile color = center.pop_tile();
			m_tiles.push_back(color);
		}
	}

	void factory::return_to_bag(bag& bag)
	{
		for (auto && tile : m_tiles)
		{
			bag.return_tile(tile);
		}
		m_tiles.clear();
	}

	std::vector<std::tuple<tile, int>> factory::get_colors_count()
	{
		std::vector<std::tuple<tile, int>> res;
		for (auto&& tile : m_tiles)
		{
			bool found = false;
			for (auto&& cq : res)
			{
				if (std::get<0>(cq) == tile)
				{
					std::get<1>(cq)++;
					found = true;
					break;
				}
			}
			if (!found)
			{
				res.emplace_back(tile, 1);
			}
		}
		return res;
	}

	int factory::tile_count(tile color)
	{
		int res(0);
		for (auto && tile : m_tiles)
		{
			if(tile == color)
			{
				++res;
			}
		}
		return res;
	}
}
