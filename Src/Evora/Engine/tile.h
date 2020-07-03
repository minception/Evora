#pragma once

#include <string>

namespace model
{
	static const int COLORS = 5;
	enum class tile
	{
		blue = 0,
		yellow,
		red,
		black,
		white,
		empty,
		starter
	};

    std::string tile_to_string(tile t);	
}
