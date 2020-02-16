#pragma once
#include "command.h"

namespace control
{
	class score_line :public command
	{
	public:
		score_line(std::shared_ptr<model::game> game, int player_index, int line)
			: command(game),
			  m_player_index(player_index),
			  m_line(line)
		{
		}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		int m_line;
		int m_score = 0;
	};
}
