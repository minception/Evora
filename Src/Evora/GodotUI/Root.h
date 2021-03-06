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
		bool m_stepping = true;
		void set_starting_player(int index);
		void move_highlight(int player_index);
		static void _register_methods();
		void _init();
		void _ready();
		void create_player_change_animations();
		void start_game();
		void step();
		void switch_to_next_player();
		void announce_winner();
		void animation_finished();
		void pattern_line_entered(int board_index, int pattern_line_index);
		void tile_over(int board_index, int pattern_line_index, int color);
		void tile_dropped(int factory_index, int color);
	};
}
