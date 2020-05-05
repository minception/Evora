#pragma once
#include "AI.h"
#include <limits>
#include <chrono>

namespace AI
{
	class MinimaxAI: public AI
	{
		int evaluate(std::shared_ptr<control::game_controller>& controller);
		bool update_scores(int player_index, int& best_score, int score);
		int minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller);
		int m_max_depth;
		std::chrono::system_clock::time_point m_end_time;
		int m_time;
		int m_alpha;
		int m_beta;
		bool m_round_finished;
		std::unique_ptr<control::command> m_best_move;
		
	public:
		void move() override;
		MinimaxAI(std::shared_ptr<control::game_controller> controller, int board_index, int time = 100) :AI(controller, board_index), m_time(time) {}
		const char* get_name() const override;
	};
}
