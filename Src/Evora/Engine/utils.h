#pragma once
#include "ai.h"
#include <chrono>

namespace utils
{
	int evaluate(std::shared_ptr<control::game_controller>& controller, int player_index);
	bool time_left(std::chrono::system_clock::time_point end_time);

	int play_game(std::vector<std::unique_ptr<ai::ai>>& players, std::shared_ptr<control::game_controller> controller, int current_player);
}
