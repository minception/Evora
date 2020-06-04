#pragma once
#include "command.h"

namespace control
{
	class score_color :public command
	{
	public:
		score_color(int player, model::tile tile)
			: m_player_index(player),
			  m_color(tile)
		{}

		void execute(std::shared_ptr<model::game> game) override;
		void unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool is_move() override;
		int player_index() override;
	private:
		int m_player_index;
		model::tile m_color;
		int m_score = 0;
	};
}
