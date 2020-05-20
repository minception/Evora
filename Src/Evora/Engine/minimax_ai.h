#pragma once
#include "ai.h"
#include <limits>
#include <chrono>

namespace ai
{
	class minimax_ai: public ai
	{
		int evaluate(std::shared_ptr<control::game_controller>& controller);
		bool update_scores(int player_index, int& best_score, int score);
		int minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller);
		bool alpha_beta_move(const std::shared_ptr<control::game_controller>& controller, std::unique_ptr<control::command> move, int& best_score, int depth, int player_index);
		int m_max_depth;
		std::chrono::system_clock::time_point m_end_time;
		int m_time;
		int m_alpha;
		int m_beta;
		bool m_round_finished;
		std::unique_ptr<control::command> m_best_move;
		
	public:
		void move() override;
		minimax_ai(std::shared_ptr<control::game_controller> controller, int board_index, int time = 100) :ai(controller, board_index), m_time(time) {}
		const char* get_name() const override;
	};
}
