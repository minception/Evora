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

		void Execute(std::shared_ptr<model::game> game) override;
		void Unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool IsMove() override;
	private:
		int m_player_index;
		model::tile m_color;
		int m_score = 0;
	};
}
