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
		std::deque<std::unique_ptr<command>> commands;
	public:
		game_controller(std::shared_ptr<model::game> model):m_model(model){}
	};
}
