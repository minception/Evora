#pragma once
#include <memory>
#include "game.h"
#include "command.h"

namespace control
{
	class drop_factory :public command
	{
	public:
		drop_factory(std::shared_ptr<model::game> game, int factory_index, int player_index, model::tile color)
			: control::command(game),
			  m_factory_index(factory_index),
			  m_player_index(player_index),
			  m_color(color)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_factory_index;
		int m_player_index;
		model::tile m_color;
		int m_moved_to_center;
		bool m_first_to_center;
		int m_moved_to_floor;
		int m_moved_to_lid;
	
	};
}
