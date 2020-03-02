#include "RandomAI.h"

namespace AI
{
	void RandomAI::move()
	{
		std::vector<std::unique_ptr<control::command>> moves = m_controller->get_possible_moves(m_board_index);
		auto start = moves.begin();
		std::uniform_int_distribution<> dis(0, (int)std::distance(start, moves.end()) - 1);
		std::advance(start, dis(m_rng));
		m_controller->add_command(std::move(*start));
		m_controller->step();
	}

	RandomAI::RandomAI(std::shared_ptr<control::game_controller> controller, int board_index) : AI(controller, board_index)
	{
		std::random_device seed;
		m_rng = std::mt19937{ seed() };
	}

	const char* RandomAI::get_name() const
	{
		return "RandomAI";
	}
}
	
