#pragma once
#include "command.h"

namespace control
{
	class final_score :public command
	{
	public:
		final_score(std::shared_ptr<model::game> game, int player_index)
			: command(game),
			  m_player_index(player_index)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		int m_score;
	};
}
