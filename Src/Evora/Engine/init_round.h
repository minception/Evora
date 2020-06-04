#pragma once
#include "command.h"

namespace control
{
	class init_round :public command
	{
	public:
		void execute(std::shared_ptr<model::game> game) override;
		void unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool is_move() override;
		int player_index() override;
	private:
		static const int FACTORY_SIZE = 4;
		int m_added_before_refill = 0;
		int m_added_after_refill = 0;
		bool m_bag_refilled = false;
		std::vector<model::tile> m_lid_state;
	};
}

