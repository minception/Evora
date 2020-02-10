#pragma once
#include "command.h"

namespace control
{
	class score_wall_tile :public command
	{
	public:
		score_wall_tile(std::shared_ptr<model::game> game, int player_index, int line_index, model::tile color)
			: command(game),
			  m_player_index(player_index),
			  m_line(line_index),
			  m_color(color)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		int m_line;
		model::tile m_color;
		int m_score;
	};
}

