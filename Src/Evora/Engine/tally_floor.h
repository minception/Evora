#pragma once
#include "command.h"

namespace control
{
	class tally_floor :public command
	{
	public:
		tally_floor(int player_index)
			: m_player_index(player_index)
		{}

		void execute(std::shared_ptr<model::game> game) override;
		void unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool is_move() override;
		int player_index() override;
	private:
		int m_player_index;
		int m_score = 0;
		int m_starter_tile_position = 0;
		// the floor size here won't include the starter tile
		int m_floor_size = 0;
	};
}
