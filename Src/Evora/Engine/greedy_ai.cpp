#include "greedy_ai.h"

#include <limits>
#include "utils.h"

using namespace ai;

void greedy_ai::move()
{
	std::vector<std::unique_ptr<control::command>> moves = m_controller->get_possible_moves(m_board_index);
	int to_execute = 0;
	float max_move_score = -std::numeric_limits<float>::max();
	std::shared_ptr<control::game_controller> mockup = std::make_unique<control::game_controller>(*m_controller);
	for (int i = 0; i < moves.size(); ++i)
	{
		mockup->add_command(std::move(moves[i]->clone()));
		mockup->step();
		float move_score = utils::evaluate(mockup, m_board_index);
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

const char* greedy_ai::get_name() const
{
	return "GreedyAI";
}

void greedy_ai::init(std::vector<std::pair<std::string, std::string>> args)
{
}
