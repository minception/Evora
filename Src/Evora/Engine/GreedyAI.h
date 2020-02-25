#pragma once
#include "AI.h"

namespace AI
{
	class GreedyAI :public AI
	{
	public:
		void move() override;
		GreedyAI(std::shared_ptr<control::game_controller> controller, int board_index):AI(controller, board_index){}
		const char* get_name() const override;
	};
}
