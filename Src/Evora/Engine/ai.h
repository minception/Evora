#pragma once
#include "game.h"
#include <memory>
#include "game_controller.h"

namespace ai
{
	/**
	 * \brief A parent class for all the ai
	 */
	class ai
	{
	protected:
		std::shared_ptr<control::game_controller> m_controller;
		int m_board_index;
		int64_t flags;
	public:
		virtual ~ai() = default;
		virtual void move() = 0;
		virtual const char* get_name() const = 0;
		virtual void init(std::vector<std::pair<std::string, std::string>> args) = 0;
		ai(std::shared_ptr<control::game_controller> controller, int board_index):m_controller(controller), m_board_index(board_index){};
	};
}
