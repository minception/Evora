#pragma once
#include <memory>
#include "game.h"
#include "command.h"

namespace control
{
	class drop_factory :public command
	{
	public:
		drop_factory(int factory_index, int player_index, model::tile color)
			: m_player_index(player_index),
			  m_factory_index(factory_index),
			  m_color(color)
		{}

		void Execute(std::shared_ptr<model::game> game) override;
		void Unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool IsMove() override;
	private:
		int m_player_index;
		int m_factory_index;
		model::tile m_color;
		int m_moved_to_center;
		bool m_first_to_center;
		int m_moved_to_floor;
		int m_moved_to_lid;
	
	};
}
