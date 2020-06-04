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

		void execute(std::shared_ptr<model::game> game) override;
		void unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool is_move() override;
		int player_index() override;
	private:
		int m_player_index;
		int m_line;
		int m_score = 0;
	};
}
