#pragma once
#include "AI.h"

#include <chrono>
#include <ctime>

#include "MCTSAlgorithm.h"

namespace AI
{
	class MonteCarloAI: public AI
	{
		std::time_t m_end_time;
		int m_time;
		std::unique_ptr<MCTSAlgorithm> m_mcts;
		std::unique_ptr<TreeNodeCreator> m_creator;
	public:
		void move() override;
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		MonteCarloAI(std::shared_ptr<control::game_controller> controller, int board_index, int time = 500);
		const char* get_name() const override;
		
	};
}
