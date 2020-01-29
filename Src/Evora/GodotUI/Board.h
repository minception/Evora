#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <OptionButton.hpp>

#include "AIFactory.h"
#include "Utils.h"

namespace godot {
	class Board : public Node2D {
		GODOT_CLASS(Board, Node2D)
		void set_highlight(bool cond);
	public:
		int index;
		bool player_select;
		
		static void _register_methods();
		void _init();
		void _process(float delta);
		void connect_children();
		void _ready();
		void _hide_player_select();
		void mouse_entered();
		void mouse_exited();
		void image_input();
	};
}
