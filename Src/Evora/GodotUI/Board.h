#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <OptionButton.hpp>

#include "AIFactory.h"
#include "Utils.h"

namespace godot
{
	class Board : public Node2D
	{
	GODOT_CLASS(Board, Node2D)
		void set_highlight(bool cond);
	public:
		int index;
		bool player_select;

		static void _register_methods();
		void _init();
		void _ready();
		void connect_children();
		void _hide_player_select();
		void mouse_entered();
		void mouse_exited();
		void pattern_line_entered(int pattern_line_index);
		void image_input();
		void set_pattern_line_highlight(int index, bool cond);
		String get_player_name();
	};
}
