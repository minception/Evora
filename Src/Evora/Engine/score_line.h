#pragma once
#include "command.h"

namespace control
{
	class score_line :public command
	{
	public:
		score_line(int player_index, int line)
			: m_player_index(player_index),
			  m_line(line)
		{
		}

		void Execute(std::shared_ptr<model::game> game) override;
		void Unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
	private:
		int m_player_index;
		int m_line;
		int m_score = 0;
	};
}
