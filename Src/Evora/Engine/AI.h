#pragma once
#include "game.h"
#include <memory>
#include "game_controller.h"

namespace AI
{
	/**
	 * \brief A parent class for all the AI
	 */
	class AI
	{
	protected:
		std::shared_ptr<control::game_controller> m_controller;
		int m_board_index;
	public:
		virtual void move() = 0;
		virtual const char* get_name() const = 0;
		AI(std::shared_ptr<control::game_controller> controller, int board_index):m_controller(controller), m_board_index(board_index){};
	};
}
