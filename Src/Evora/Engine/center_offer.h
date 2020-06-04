#pragma once
#include "command.h"

namespace control
{
	class center_offer :public command
	{
	public:
		center_offer(int player_index, int pattern_line_index, model::tile color)
			: m_player_index(player_index),
			  m_pattern_line_index(pattern_line_index),
			  m_color(color)
		{}

		void execute(std::shared_ptr<model::game> game) override;
		void unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool is_move() override;
		int player_index() override;
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
