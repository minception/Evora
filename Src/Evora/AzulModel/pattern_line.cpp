#include "pattern_line.h"

namespace model
{
	bool pattern_line::is_full() const
	{
		return m_count == m_size;
	}

	bool pattern_line::add_tiles(int count, tile color, floor& floor, lid& lid, bool first_center)
	{
		if (m_color != tile::empty || m_color != color || is_full()) return false;
		m_count += count;
		// when taking a first tile_wall from the center also add a starter tile_wall to the floor
		if (first_center && !floor.is_full()) floor.add_tiles(tile::starter, 1, lid);
		if(m_count > m_size)
		{
			floor.add_tiles(color, m_count - m_size, lid);
			m_count = m_size;
		}
		return true;
	}

	void pattern_line::clear(lid& lid)
	{
		lid.add_tiles(m_color, m_size - 1); // one tile_wall goes to wall
		m_count = 0;
		m_color = tile::empty;
	}

	bool pattern_line::can_put_color(tile color) const
	{
		return !is_full() && (m_color == tile::empty || m_color == color);
	}
}
