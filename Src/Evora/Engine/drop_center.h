#pragma once
#include "command.h"

namespace control
{
	class drop_center :public command
	{
	public:
		drop_center(std::shared_ptr<model::game> game, int player_index, model::tile color)
			: command(game),
			m_player_index(player_index),
			m_color(color)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		model::tile m_color;
		std::vector<int> m_tile_indices;
		int m_moved_to_floor;
		int m_moved_to_lid;
		bool m_starter_tile;
	};
}
