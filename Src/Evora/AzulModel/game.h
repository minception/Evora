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
		virtual bool tile_walls();

		// game information retrieval methods
		bool can_factory_offer(int player, int factory, tile color, int line);
		bool can_center_offer(int player, tile color, int line);
		int get_winner();
		bool factories_empty();
		bool center_empty() const;
		int factory_count() const;
		int player_count() const;

		// game initialization methods
		void fill_factories();
		void shuffle_bag();

		// iterator methods for display purposes
		std::vector<factory>::const_iterator factories_begin() const;
		std::vector<factory>::const_iterator factories_end() const;
		std::vector<board>::const_iterator players_begin() const;
		std::vector<board>::const_iterator players_end() const;
		std::vector<tile>::const_iterator center_begin() const;
		std::vector<tile>::const_iterator center_end() const;

		// control functions
		virtual std::tuple<int, int> factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color);
		virtual int add_to_floor(int player_index, int count, tile color);
		void add_to_lid(int count, tile color);
		virtual std::tuple<int, int, std::vector<int>> center_to_pattern_line(int player_index, int pattern_line_index, tile color);
	};
}
