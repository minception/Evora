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
		float time_remaining;

	static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		void connect_children();
		void _hide_player_select();
		void mouse_entered();
		void mouse_exited();
		void pattern_line_entered(int pattern_line_index);
		void tile_moved(Vector2 position, int color);
		void tile_over(int pattern_line_index, int color);
		void image_input();
		void set_pattern_line_highlight(int index, bool cond);
		String get_player_name();
		int get_pattern_line_hover_index();
		std::vector<Vector2> get_pattern_line_positions(int pattern_line_index, int count);
		std::vector<Vector2> get_floor_positions(int count);
		std::vector<Vector2> get_wall_color_positions(int color);
		Vector2 get_wall_position(int line, int color);
		Vector2 get_starter_tile_position();
		void display_wall_tile_score(const std::vector<int>& score_indices, int line, int color, int score);
		void display_wall_color_score(int color, int score);
		void display_wall_line_score(int line, int score);
		void display_wall_row_score(int row, int score);
		void increase_score(int score);
		void set_floor_highlight(bool cond);
		void display_floor_score(int score);
	};
}
