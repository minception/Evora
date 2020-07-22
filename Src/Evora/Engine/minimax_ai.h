#pragma once
#include "ai.h"
#include <limits>
#include <chrono>

namespace ai
{
	class minimax_ai: public ai
	{
		bool update_scores(int player_index, float& best_score, float score, float& alpha, float& beta);
		float minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller, float alpha, float beta);
		bool alpha_beta_move(const std::shared_ptr<control::game_controller>& controller, std::unique_ptr<control::command> move, float& best_score, int depth, int player_index, float& alpha, float& beta);
		int m_max_depth = 0;
		bool m_fixed_depth = false;
		std::chrono::system_clock::time_point m_end_time;
		int m_time;
		bool m_round_finished = false;
		std::unique_ptr<control::command> m_best_move;

	public:
		void move() override;
		minimax_ai(std::shared_ptr<control::game_controller> controller, int board_index, int time = 100) :ai(controller, board_index), m_time(time) {}
		const char* get_name() const override;
		void init(std::vector<std::pair<std::string, std::string>> args) override;
	};
}
