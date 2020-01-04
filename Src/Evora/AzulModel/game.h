#pragma once

#include "bag.h"
#include "center.h"
#include "factory.h"
#include "lid.h"
#include "board.h"

namespace model
{
	class game
	{
		bag m_bag;
		center m_center;
		std::vector<factory> m_factories;
		lid m_lid;
		std::vector<board> m_players;
		int m_current_player;
	public:
		game(int number_of_players);
		bool factory_offer(int player, int factory, tile color, int line);
		bool center_offer(int player, tile color, int line);
		bool tile_walls();
		int get_winner();
		bool factories_empty();
		bool center_empty() const;
	};
}
