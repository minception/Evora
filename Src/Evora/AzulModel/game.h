#pragma once

#include "bag.h"
#include "center.h"
#include "factory.h"
#include "lid.h"
#include "player.h"

namespace model
{
	class game
	{
		bag m_bag;
		center m_center;
		std::vector<factory> m_factories;
		lid m_lid;
		std::vector<player> m_players;
	public:
		game(int number_of_players);
	};
}
