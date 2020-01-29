#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>

namespace godot {
	class Board : public Node2D {
		GODOT_CLASS(Board, Node2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		Board();
	};

	inline void Board::_ready()
	{
		
	}
}
