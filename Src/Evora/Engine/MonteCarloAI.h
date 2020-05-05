#pragma once
#include "AI.h"
#include <ctime>
#include <chrono>

namespace AI
{
	class MonteCarloAI: public AI
	{
		std::time_t m_end_time;
		int m_time;
	public:
		void move() override;
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		MonteCarloAI(std::shared_ptr<control::game_controller> controller, int board_index, int time = 500) :AI(controller, board_index), m_time(time)
		{
			{
				m_end_time = std::chrono::system_clock::to_time_t(now + std::chrono::milliseconds(time));
			}
		}
		const char* get_name() const override;
		
	};
}
