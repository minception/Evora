#pragma once

#include <vector>
#include <array>

#include "Tile.h"
#include "Lid.h"

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
		/**
		 * \brief Finding a first empty spot in a pattern line
		 * \param patternLine A pattern line to check
		 * \return An index of a first empty spot on the pattern line or -1 if the pattern line is empty
		 */
		int first_empty_spot(size_t patternLine);
	public:
		player();
		matrix_line_iterator wall_begin() const;
		matrix_line_iterator wall_end() const;
		matrix_line_iterator pattern_lines_begin() const;
		matrix_line_iterator pattern_lines_end() const;
		floor_iterator floor_begin() const;
		floor_iterator floor_end() const;
		int32_t get_score() const;
		bool put_to_floor(type type);
		bool put_to_pattern_line(size_t patternLine, type color, size_t count);
	};
}
