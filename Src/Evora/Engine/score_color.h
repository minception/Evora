#pragma once
#include "command.h"

namespace control
{
	class score_color :public command
	{
	public:
		score_color(std::shared_ptr<model::game> game, int player, model::tile tile)
			: command(game),
			  m_player_index(player),
			  m_color(tile)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		model::tile m_color;
		int m_score = 0;
	};
}
