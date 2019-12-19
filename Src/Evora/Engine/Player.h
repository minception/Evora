#pragma once

#include <array>

#include "Tile.h"

namespace engine {
	class Player
	{
	private:
		std::array<std::array<Tile, 5>, 5> m_patternLine; // TODO:emulate cascading lines here
		std::array<std::array<Tile, 5>, 5> m_wall;
		int32_t m_score = 0;
	};
}
