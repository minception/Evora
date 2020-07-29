#pragma once
#include "ai.h"
#include <chrono>

#include "logger.h"

namespace utils
{
	bool time_left(std::chrono::system_clock::time_point end_time);

	int play_game(std::vector<std::unique_ptr<ai::ai>>& players, std::shared_ptr<control::game_controller> controller, int current_player, std::shared_ptr<logging::logger> logger);
}
