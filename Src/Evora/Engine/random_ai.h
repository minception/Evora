#pragma once
#include "ai.h"
#include <random>

namespace ai
{
	class random_ai :public ai
	{
		 std::mt19937 m_rng;
	public:
		void move() override;
		random_ai(std::shared_ptr<control::game_controller> controller, int board_index);
		const char* get_name() const override;
	};
}
