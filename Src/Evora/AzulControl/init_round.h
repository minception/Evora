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
		bool m_bag_refilled;
		std::vector<model::tile> lid_state;
	};
}

