#pragma once
#include "ai.h"
#include "strategy_move.h"
#include <map>

namespace ai
{
	class strategy_ai: public ai
	{
	public:
		void move() override;
		strategy_ai(std::shared_ptr<control::game_controller> controller, int board_index) :ai(controller, board_index) {}
		const char* get_name() const override;
	private:
		std::map<int, std::vector<strategy_move>> sort_moves(const std::vector<strategy_move>& moves);
		std::vector<std::pair<int, float>> calculate_possible_fill(const std::map<int, std::vector<strategy_move>>& sorted_moves);
		std::tuple<int, int> calculate_coordinates(int position);
		const strategy_move& best_fill(const std::vector<strategy_move>& moves);
		std::unique_ptr<control::command> pick_move();
		std::vector<strategy_move> get_moves();
	public:
		void init(std::vector<std::pair<std::string, std::string>> args) override;
	};
}
