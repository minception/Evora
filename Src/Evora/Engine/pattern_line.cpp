#include "pattern_line.h"

namespace model
{
	bool pattern_line::full()
	{
		return m_size == m_count;
	}

	void pattern_line::add(tile tile)
	{
		m_color = tile;
		m_count++;
	}

	bool pattern_line::can_add(tile tile)
	{
		if(m_color == tile::empty)
		{
			return true;
		}
		if(full() || m_color != tile)
		{
			return false;
		}
		return true;
	}

	tile pattern_line::get_color()
	{
		return m_color;
	}

	void pattern_line::clear()
	{
		m_color = tile::empty;
		m_count = 0;
	}

	void pattern_line::remove_tiles(int count)
	{
		m_count -= count;
		if(m_count == 0)
		{
			m_color = tile::empty;
		}
	}

	void pattern_line::fill(tile tile)
	{
		m_count = m_size;
		m_color = tile;
	}
}
