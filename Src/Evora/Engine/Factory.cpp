#include "Factory.h"

namespace engine {
	factory::factory()
	{
		for (size_t i = 0; i < MAX_TILES; ++i)
		{
			m_tiles.emplace_back(type::empty);
		}
	}
}
