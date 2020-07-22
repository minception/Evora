#pragma once
#include "ai.h"

namespace ai
{
	class greedy_ai :public ai
	{
	public:
		void move() override;
		greedy_ai(std::shared_ptr<control::game_controller> controller, int board_index):ai(controller, board_index){}
		const char* get_name() const override;
		void init(std::vector<std::pair<std::string, std::string>> args) override;
	};
}
