#pragma once

#include<vector>

#include "Tile.h"
#include "Bag.h"
#include "Center.h"

namespace engine {
	using factory_iterator = std::vector<tile>::const_iterator;
	class factory
	{
	private:
		static const uint32_t MAX_TILES = 4;
		std::vector<tile> m_tiles;
	public:
		factory();;
		// Fill the factory from the bag
		bool fill(bag& bag);
		int get_tiles_of_color(type color);
		void empty_to_center(center& center);
		factory_iterator begin() const;
		factory_iterator end() const;
	};
}
