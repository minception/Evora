#include "Lid.h"

namespace engine {
	lid::lid()
	{
	}

	bool lid::get_tile(tile& out)
	{
		if(is_empty())
		{
			return false;
		}
		out = m_tiles.back();
		m_tiles.pop_back();
		return true;
	}
}
