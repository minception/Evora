#pragma once

#include "bag.h"
#include "board.h"
#include "center.h"
#include "factory.h"
#include "lid.h"

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

		// game control methods
		virtual bool factory_offer(int player, int factory, tile color, int line);
		virtual bool center_offer(int player, tile color, int line);
		virtual bool tile_walls();

		// game information retrieval methods
		bool can_factory_offer(int player, int factory, tile color, int line);
		bool can_center_offer(int player, tile color, int line);
		int get_winner();
		bool factories_empty();
		bool center_empty() const;
		int factory_count() const;
		int player_count() const;

		// iterator methods for display purposes
		std::vector<factory>::const_iterator factories_begin() const;
		std::vector<factory>::const_iterator factories_end() const;
		std::vector<board>::const_iterator players_begin() const;
		std::vector<board>::const_iterator players_end() const;
		std::vector<tile>::const_iterator center_begin() const;
		std::vector<tile>::const_iterator center_end() const;
	};
}
