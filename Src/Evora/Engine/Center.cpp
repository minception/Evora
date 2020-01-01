#include "Center.h"
#include <tuple>

namespace engine
{
	void center::add_tile(const type color)
	{
		m_tiles.emplace_back(color);
	}

	std::tuple<bool, int> center::get_tiles_of_color(type color)
	{
		int res = 0;
		auto i = m_tiles.begin();
		while(i != m_tiles.end())
		{
			if(i->get_type() == color)
			{
				++res;
				m_tiles.erase(i);
			}
			i++;
		}
		if(!m_first_took)
		{
			m_first_took = true;
			return { true, res };
		}
		return { false, res };
	}

	center_iterator center::begin() const
	{
		return m_tiles.cbegin();
	}

	center_iterator center::end() const
	{
		return m_tiles.cend();
	}

	tile center::operator[](size_t i) const
	{
		return m_tiles[i];
	}
}
