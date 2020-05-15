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
		int m_current_player;
		bool m_game_over = false;
	public:
		game_controller(std::shared_ptr<model::game> model):m_model(model){}
		game_controller(const game_controller& other);
		void start_game();
		void add_command(std::unique_ptr<command> command);
		void set_first_player(int player_index);
		int add_wall_tiling_faze();
		int add_game_end();
		std::vector<std::unique_ptr<command>> get_possible_moves(int player_index);
		int possible_moves_count(int player_index);
		bool step();
		bool is_round_over();
		void step_back();
		int evaluate_state(int player_index);
		bool game_over();
		int get_winner();
		int get_score(int player_index);
		int get_first_player();
		std::shared_ptr<model::game> get_model();
	};
}
