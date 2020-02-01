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
}
