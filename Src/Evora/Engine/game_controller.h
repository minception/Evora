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
	public:
		game_controller(std::shared_ptr<model::game> model):m_model(model){}
		void start_game();
		bool step();
		
	};
}
