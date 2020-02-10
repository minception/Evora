#pragma once

#include <vector>

#include "floor.h"
#include "pattern_line.h"
#include "wall.h"

namespace model
{
	class board
	{
		int m_score{0};
		std::vector<pattern_line> m_pattern_lines;
		wall m_wall;
		floor m_floor;
		bool m_has_starter_tile;
	public:
		board();
		void tile_wall(int pattern_line_index, tile color);
		int get_score() const;

		// iterator methods for display purposes
		std::vector<std::vector<tile>>::const_iterator wall_begin() const;
		std::vector<std::vector<tile>>::const_iterator wall_end() const;
		std::vector<pattern_line>::const_iterator pattern_lines_begin() const;
		std::vector<pattern_line>::const_iterator pattern_lines_end() const;
		std::vector<tile>::const_iterator floor_begin() const;
		std::vector<tile>::const_iterator floor_end() const;
		void add_to_floor(tile color);
		bool has_starter_tile();
		void set_starter_tile(bool cond);
		bool pattern_line_full(int pattern_line_index);
		void add_to_pattern_line(int pattern_line_index, tile tile);
		bool floor_full();
		bool can_add_to_pattern_line(int pattern_line_index, tile tile);
		void take_starter_tile();
		void set_starter_player();
		tile pattern_line_color(int pattern_line_index);
		void clear_pattern_line(int pattern_line_index);
		int score_wall_tile(int pattern_line_index, tile tile);
	};
}
