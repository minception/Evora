﻿#pragma once

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
		bool tile_wall(lid& lid);
		int get_score() const;

		// iterator methods for display purposes
		std::vector<std::vector<tile>>::const_iterator wall_begin() const;
		std::vector<std::vector<tile>>::const_iterator wall_end() const;
		std::vector<pattern_line>::const_iterator pattern_lines_begin() const;
		std::vector<pattern_line>::const_iterator pattern_lines_end() const;
		std::vector<tile>::const_iterator floor_begin() const;
		std::vector<tile>::const_iterator floor_end() const;
		int add_to_floor(int count, tile color);
		bool has_starter_tile();
		void set_starter_tile(bool cond);
	};
}