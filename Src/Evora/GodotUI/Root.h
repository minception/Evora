#pragma once

#include <core/Godot.hpp>
#include <memory>
#include <Node2D.hpp>

#include "GodotGame.h"
#include "Board.h"
#include "GodotTile.h"


namespace godot
{
	class GodotGame;
	class TileLoader;
	class Root :public Node2D
	{
		GODOT_CLASS(Root, Node2D)
		
		int m_number_of_players;

		void add_start_button();
	public:
		void set_starting_player(int index);
		static void _register_methods();
		void _init();
		void _ready();
		void start_game();
		void animation_finished();
		void pattern_line_entered(int pattern_line_index, int board_index);
	};
}
