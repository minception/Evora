#include "center.h"
#include <algorithm>

namespace model
{
	void center::add_tile(tile type)
	{
		m_tiles.emplace_back(type);
	}

	bool center::empty() const
	{
		return m_tiles.empty();
	}

	int center::offer(tile color)
	{
		int res = 0;
		for (auto && tile : m_tiles)
		{
			if (tile == color) ++res;
		}
		return res;
	}

	int center::offer(tile color, bool& first)
	{
		int res = 0;
		for (auto && tile : m_tiles)
		{
			if (tile == color) ++res;
		}
		first = first_pick;
		return res;
	}
	std::tuple<int, std::vector<int>> center::pick_color(tile color)
	{
		std::vector<int> res;
		int index = 0;
		int count = 0;
		std::remove_if(m_tiles.begin(), m_tiles.end(), [&res, &index, &count, color](tile tile)
		{
			if(tile == color)
			{
				res.push_back(index);
				++count;
				++index;
				return true;
			}
			++index;
			return false;
		});
		return { count, res };
	}

	std::vector<tile>::const_iterator center::begin() const
	{
		return m_tiles.cbegin();
	}

	std::vector<tile>::const_iterator center::end() const
	{
		return m_tiles.cend();
	}
}
