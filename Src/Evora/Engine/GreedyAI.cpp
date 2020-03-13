#include "GreedyAI.h"

#include <limits>
#include "utils.h"

using namespace AI;

void GreedyAI::move()
{
	std::vector<std::unique_ptr<control::command>> moves = m_controller->get_possible_moves(m_board_index);
	//printf("Width: %d\n", moves.size());
	int to_execute = 0;
	int max_move_score = std::numeric_limits<int>::min();
	std::shared_ptr<control::game_controller> mockup = std::make_unique<control::game_controller>(*m_controller);
	for (int i = 0; i < moves.size(); ++i)
	{
		mockup->add_command(std::move(moves[i]->clone()));
		mockup->step();
		int move_score = utils::evaluate(mockup, m_board_index);
		if(move_score > max_move_score)
		{
			max_move_score = move_score;
			to_execute = i;
		}
		mockup->step_back();
	}
	m_controller->add_command(std::move(moves[to_execute]));
	m_controller->step();
}

const char* GreedyAI::get_name() const
{
	return "GreedyAI";
}
