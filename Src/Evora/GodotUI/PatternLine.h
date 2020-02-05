#pragma once
#include <core/Godot.hpp>
#include <TextureRect.hpp>
#include <Node2D.hpp>
#include <vector>

namespace godot
{
	class PatternLine :public Node2D
	{
		GODOT_CLASS(PatternLine, Node2D)
		int m_index;
		int m_tile_count;
	public:
		void set_index(int index) { m_index = index;}
		int get_index() const { return m_index; }
		std::vector<Vector2> get_n_positions(int n);
		static void _register_methods();
		void _init();
		void _ready();
		void mouse_entered();
		void mouse_exited();
		void set_highlight(bool cond);
		void tile_moved(Vector2 position, int color);
		void input();
		bool is_mouse_over();
	};
}
