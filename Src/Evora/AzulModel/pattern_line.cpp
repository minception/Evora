#include "pattern_line.h"

namespace model
{
	bool pattern_line::is_full() const
	{
		return m_count == m_size;
	}

	std::tuple<int, int> pattern_line::add_tiles(int count, tile color)
	{
		m_color = color;
		m_count += count;
		if (m_count > m_size)
		{
			int overflow = m_count - m_size;
			m_count = m_size;
			return { count - overflow, overflow };
		}
		return { count, 0 };
	}

	void pattern_line::clear(lid& lid)
	{
		lid.add_tiles(m_size - 1, m_color); // one tile_wall goes to wall
		m_count = 0;
		m_color = tile::empty;
	}

	bool pattern_line::can_put_color(tile color) const
	{
		return !is_full() && (m_color == tile::empty || m_color == color);
	}
}
