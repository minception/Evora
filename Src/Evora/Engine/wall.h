#pragma once

#include <vector>

#include "tile.h"

namespace model
{
	class wall
	{
		static const int COLOR_SCORE = 10;
		static const int ROW_SCORE = 7;
		static const int LINE_SCORE = 2;
		std::vector<std::vector<tile>> m_tiles;
		int score(int x, int y);
		int horizontal_score(int x, int y);
		int vertical_score(int x, int y);
		
	public:
		wall();
		bool full_line(int line);

		// iterator methods for display purposes
		std::vector<std::vector<tile>>::const_iterator begin() const;
		std::vector<std::vector<tile>>::const_iterator end() const;
		
		void add_tile(int pattern_line_index, tile tile);
		int score_tile(int pattern_line_index, tile tile);
		std::vector<int> get_score_indices(int pattern_line_index, tile tile);
		bool game_finished();
		int score_color(tile color);
		int score_row(int row);
		int score_line(int line);
		bool empty(int pattern_line_index, tile tile);
		int line_count(int line);
	};
}
