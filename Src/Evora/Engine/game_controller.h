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
		int current_command = 0;
		void add_wall_tiling_faze();
	public:
		game_controller(std::shared_ptr<model::game> model):m_model(model){}
		void start_game();
		void add_command(std::unique_ptr<command> command);
		void set_first_player(int player_index);
		void add_game_end();
		std::vector<std::unique_ptr<command>> get_possible_moves(int player_index);
		bool step();
	};
}
