#pragma once
#include "AI.h"
#include <chrono>

namespace utils
{
	int evaluate(std::shared_ptr<control::game_controller>& controller, int player_index);
	bool timeLeft(std::chrono::system_clock::time_point end_time);

	int play_game(std::vector<std::unique_ptr<AI::AI>>& players, std::shared_ptr<control::game_controller> controller, int current_player);
}
