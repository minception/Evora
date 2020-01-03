#include "pattern_line.h"

namespace model
{
	bool pattern_line::is_full() const
	{
		return m_count == m_size;
	}

	bool pattern_line::add_tiles(int count, tile color, floor& floor, lid& lid)
	{
		if (m_color != tile::empty || m_color != color || is_full()) return false;
		m_count += count;
		if(m_count > m_size)
		{
			floor.add_tiles(color, m_count - m_size, lid);
			m_count = m_size;
		}
	}

	void pattern_line::clear(lid& lid)
	{
		lid.add_tiles(m_color, m_size - 1); // one tile goes to wall
		m_count = 0;
		m_color = tile::empty;
	}
}
