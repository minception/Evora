#pragma once

#include <vector>
#include <array>

#include "Tile.h"

namespace engine {
	using matrix_line_iterator = std::vector<std::vector<tile>>::const_iterator;
	using floor_iterator = std::vector<tile>::const_iterator;
	class player
	{
	private:
		static const uint32_t WALL_SIZE = 5;
		static const uint32_t PATTERN_LINE_SIZE = 5;
		static const uint32_t FLOOR_SIZE = 7;
		std::vector<std::vector<tile>> m_patternLine;
		std::vector<std::vector<tile>> m_wall;
		std::vector<tile> m_floor;
		static const std::array<int32_t, FLOOR_SIZE> FLOOR_SCORE;
		int32_t m_score = 0;
	public:
		player();
		matrix_line_iterator wall_begin() const;
		matrix_line_iterator wall_end() const;
		matrix_line_iterator pattern_lines_begin() const;
		matrix_line_iterator pattern_lines_end() const;
		floor_iterator floor_begin() const;
		floor_iterator floor_end() const;
	};
}
