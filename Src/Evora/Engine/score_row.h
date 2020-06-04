#pragma once
#include "command.h"

namespace control
{
	class score_row :public command
	{
		
	public:
		score_row(int player_index, int row)
			: m_player_index(player_index),
			  m_row(row)
		{
		}

		void execute(std::shared_ptr<model::game> game) override;
		void unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool is_move() override;
		int player_index() override;
	private:
		int m_player_index;
		int m_row;
		int m_score = 0;
	};
}
