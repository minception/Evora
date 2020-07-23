#pragma once
#include "game_controller.h"

namespace utils
{
	float evaluate(std::shared_ptr<control::game_controller>& controller, int player_index);
	double score_move(std::shared_ptr<control::game_controller> controller, int factory_index, int player_index, int pattern_line_index, model::tile color);
	std::vector<std::pair<std::unique_ptr<control::command>, double>> get_scored_moves(std::shared_ptr<control::game_controller> controller, int player_index);
}
