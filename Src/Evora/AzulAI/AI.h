#pragma once
#include "game.h"
#include <memory>
#include "../AzulControl/game_controller.h"

namespace AI
{
	class AI
	{
		std::shared_ptr<control::game_controller> m_controller;
	public:
		virtual void move() = 0;
		virtual const char* get_name() const = 0;
		AI(std::shared_ptr<control::game_controller> controller):m_controller(controller){};
	};
}
