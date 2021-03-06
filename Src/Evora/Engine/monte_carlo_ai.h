﻿#pragma once
#include "ai.h"

#include <chrono>
#include <ctime>

#include "mcts_algorithm.h"

namespace ai
{
	class monte_carlo_ai: public ai
	{
		int m_time;
		int m_iterations;
		std::unique_ptr<mcts_algorithm> m_mcts;
		std::unique_ptr<tree_node_creator> m_creator;
	public:
		void move() override;
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		monte_carlo_ai(std::shared_ptr<control::game_controller> controller, int board_index, int iterations = 500, int time = -1);
		const char* get_name() const override;

		bool init(std::vector<std::pair<std::string, std::string>> args) override;
	};
}
