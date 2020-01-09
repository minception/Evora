#pragma once

#include "floor.h"
#include "lid.h"
#include "tile.h"

namespace model
{
	class pattern_line
	{
		tile m_color{ tile::empty };
		int m_size;
		int m_count{ 0 };
	public:
		pattern_line(int size) :m_size(size) {}
		bool is_full() const;
		bool add_tiles(int count, tile color, floor& floor, lid& lid, bool first_center = false);
		void clear(lid& lid);
		tile get_color() const { return m_color; }
		int get_count() const { return m_count; }
		bool can_put_color(tile color) const;

	};
}
