#pragma once
#include "command.h"

namespace control
{
	class drop_center :public command
	{
	public:
		drop_center(int player_index, model::tile color)
			: m_player_index(player_index),
			  m_color(color)
		{}

		void Execute(std::shared_ptr<model::game> game) override;
		void Unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool IsMove() override;
	private:
		int m_player_index;
		model::tile m_color;
		std::vector<int> m_tile_indices;
		int m_moved_to_floor;
		int m_moved_to_lid;
		bool m_starter_tile;
	};
}
