#pragma once
#include "command.h"

namespace control
{
	class init_round :public command
	{
	public:
		init_round(std::shared_ptr<model::game> game)
			: command(game)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		static const int FACTORY_SIZE = 4;
		int m_added_before_refill = 0;
		int m_added_after_refill = 0;
		bool m_bag_refilled = false;
		std::vector<model::tile> m_lid_state;
	};
}

