#pragma once

#include <vector>

#include "tile.h"

namespace model
{
	class wall
	{
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
	};
}
