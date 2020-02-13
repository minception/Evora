#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <vector>

namespace godot
{
	class Center :public Node2D
	{
		GODOT_CLASS(Center, Node2D)
		int m_tile_count;
		int m_tiles_per_line;
	public:
		static void _register_methods();
		void _init();
		std::vector<Vector2> get_n_positions(int n);
		std::vector<Vector2> get_rearrange_positions();
		void take_n_tiles(int n);
	};
}
