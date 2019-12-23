#pragma once

#include <array>

#include "Tile.h"

namespace engine {
	class Player
	{
	private:
		static const uint32_t WALL_SIZE = 5;
		static const uint32_t PATTERN_LINE_SIZE = 5;
		static const uint32_t FLOOR_SIZE = 7;
		std::array<std::array<Tile, WALL_SIZE>, WALL_SIZE> m_patternLine; // TODO:emulate cascading lines here
		std::array<std::array<Tile, PATTERN_LINE_SIZE>, PATTERN_LINE_SIZE> m_wall;
		std::array<Tile, FLOOR_SIZE> m_floor;
		static const std::array<int32_t, FLOOR_SIZE> FLOOR_SCORE;
		int32_t m_score = 0;
	public:
		Player();
		~Player();
	};
}
