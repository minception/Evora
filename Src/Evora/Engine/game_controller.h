#pragma once
#include "game.h"
#include <memory>
#include "command.h"
#include <deque>

namespace control
{
	class game_controller
	{
		std::shared_ptr<model::game> m_model;
		std::deque<std::unique_ptr<command>> m_commands;
		int m_current_command = 0;
		int m_current_player = 0;
		int round = 0;
		bool m_game_over = false;
	public:
		game_controller(std::shared_ptr<model::game> model):m_model(model){}
		game_controller(const game_controller& other);
		void start_game(int first_player);
		void add_command(std::unique_ptr<command> command);
		int get_current_player();
		void set_first_player(int player_index);
		int add_wall_tiling_phase();
		int add_game_end();
		std::vector<std::unique_ptr<command>> get_possible_moves(int player_index);
		int possible_moves_count(int player_index);
		bool step();
		bool is_round_over();
		void step_back();
		void player_move_back();
		void player_move();
		int evaluate_state(int player_index);
		bool game_over();
		int get_winner();
		int get_score(int player_index);
		int get_first_player();
		std::shared_ptr<model::game> get_model();
	};
}
