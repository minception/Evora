#pragma once
#include "command.h"

namespace control
{
	class center_offer :public command
	{
	public:
		center_offer(std::shared_ptr<model::game> game, int player_index, int pattern_line_index, model::tile color)
			: command(game),
			  m_player_index(player_index),
			  m_pattern_line_index(pattern_line_index),
			  m_color(color)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		int m_pattern_line_index;
		model::tile m_color;
		std::vector<int> m_tile_indices;
		int m_moved_to_pattern_line;
		int m_moved_to_floor;
		int m_moved_to_lid;
		bool m_starter_tile;
	};
}
