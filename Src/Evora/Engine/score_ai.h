#pragma once
#include "ai.h"

namespace ai
{
	class score_ai :public ai
	{
	public:
		void move() override;
		score_ai(std::shared_ptr<control::game_controller> controller, int board_index):ai(controller, board_index){}
		const char* get_name() const override;
	};
}
