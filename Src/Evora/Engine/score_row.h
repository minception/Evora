#pragma once
#include "command.h"

namespace control
{
	class score_row :public command
	{
		
	public:
		score_row(std::shared_ptr<model::game> game, int player_index, int row)
			: command(game),
			  m_player_index(player_index),
			  m_row(row)
		{
		}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		int m_row;
		int m_score = 0;
	};
}
