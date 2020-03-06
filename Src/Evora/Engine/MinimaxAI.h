#pragma once
#include "AI.h"

namespace AI
{
	class MinimaxAI: public AI
	{
		int evaluate_move(int player_index, int depth, std::shared_ptr<control::game_controller> controller);
	public:
		void move() override;
		MinimaxAI(std::shared_ptr<control::game_controller> controller, int board_index) :AI(controller, board_index) {}
		const char* get_name() const override;
	};
}
