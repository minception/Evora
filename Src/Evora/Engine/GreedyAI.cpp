#include "GreedyAI.h"

#include <limits>

using namespace AI;

void GreedyAI::move()
{
	std::vector<std::unique_ptr<control::command>> moves = m_controller->get_possible_moves(m_board_index);
	int to_execute = 0;
	int max_move_score = std::numeric_limits<int>::min();
	control::game_controller mockup{ *m_controller };
	for (int i = 0; i < moves.size(); ++i)
	{
		mockup.add_command(std::move(moves[i]->clone()));
		mockup.step();
		int move_score = mockup.evaluate_state(m_board_index);
		if(move_score > max_move_score)
		{
			max_move_score = move_score;
			to_execute = i;
		}
		mockup.step_back();
	}
	m_controller->add_command(std::move(moves[to_execute]));
	m_controller->step();
}

const char* GreedyAI::get_name() const
{
	return "GreedyAI";
}
