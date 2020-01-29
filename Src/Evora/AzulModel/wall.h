#pragma once

#include <map>
#include <vector>

#include "lid.h"
#include "pattern_line.h"
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
	};
}
