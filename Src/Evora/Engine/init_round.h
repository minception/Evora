#pragma once
#include "command.h"

namespace control
{
	class init_round :public command
	{
	public:
		void Execute(std::shared_ptr<model::game> game) override;
		void Unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
	private:
		static const int FACTORY_SIZE = 4;
		int m_added_before_refill = 0;
		int m_added_after_refill = 0;
		bool m_bag_refilled = false;
		std::vector<model::tile> m_lid_state;
	};
}

