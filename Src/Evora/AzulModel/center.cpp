#include "center.h"

namespace model
{
	void center::add_tile(tile type)
	{
		m_tiles.emplace_back(type);
	}
}
