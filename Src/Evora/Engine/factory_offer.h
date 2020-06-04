#pragma once
#include "command.h"

namespace control
{
	class factory_offer :public command
	{
	public:
		factory_offer(int factory_index, int player_index, int pattern_line_index, model::tile color)
			: m_player_index(player_index),
			  m_factory_index(factory_index),
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
		int m_factory_index;
		int m_pattern_line_index;
		model::tile m_color;
		int m_moved_to_pattern_line;
		int m_moved_to_center;
		bool m_first_to_center;
		int m_moved_to_floor;
		int m_moved_to_lid;
	};
}

