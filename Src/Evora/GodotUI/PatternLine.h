#pragma once
#include <core/Godot.hpp>
#include <TextureRect.hpp>
#include <Node2D.hpp>

namespace godot
{
	class PatternLine :public Node2D
	{
		GODOT_CLASS(PatternLine, Node2D)
		int m_index;
	public:
		void set_index(int index) { m_index = index;}
		int get_index() const { return m_index; }
		static void _register_methods();
		void _init();
		void _ready();
		void mouse_entered();
		void mouse_exited();
		void set_highlight(bool cond);
		void tile_moved(Vector2 position, int color);
		void input();
	
	};
}
