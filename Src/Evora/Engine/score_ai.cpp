#include "score_ai.h"

#include <limits>
#include "utils.h"

using namespace ai;

// Always choose the move with the highest score from utils::score_move.
void score_ai::move()
{
	std::vector<std::pair<std::unique_ptr<control::command>, double>> moves =
        utils::get_scored_moves(m_controller, m_board_index);
	
    auto max = std::max_element(moves.begin(), moves.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

	m_controller->add_command(std::move(max->first));
	m_controller->step();
}

const char* score_ai::get_name() const
{
	return "ScoreAI";
}
