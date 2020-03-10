#pragma once
#include "AI.h"
#include <limits>

namespace AI
{
	class MinimaxAI: public AI
	{
		int evaluate(std::shared_ptr<control::game_controller>& controller);
		int minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller);
		int m_alpha = std::numeric_limits<int>::min();
		int m_beta = std::numeric_limits<int>::max();
		int m_max_depth;
	public:
		void move() override;
		MinimaxAI(std::shared_ptr<control::game_controller> controller, int board_index) :AI(controller, board_index) {}
		const char* get_name() const override;
	};
}
