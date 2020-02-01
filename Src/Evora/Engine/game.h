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
		std::vector<board> m_boards;
		//TODO: set this variable when initializing round
		bool m_starter_tile_handled; // keeps track of whether the starter tile has been handled this factory offer round
	public:
		game(int number_of_players);
		int factory_count();
		int player_count();

		// iterator methods for display purposes
		std::vector<factory>::const_iterator factories_begin() const;
		std::vector<factory>::const_iterator factories_end() const;
		std::vector<board>::const_iterator players_begin() const;
		std::vector<board>::const_iterator players_end() const;
		std::vector<tile>::const_iterator center_begin() const;
		std::vector<tile>::const_iterator center_end() const;

		void shuffle_bag();
		std::vector<tile> get_lid_state();
		void refill_bag();

		// functions affecting gui
		virtual int bag_to_factories();
		virtual int factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color);
		virtual int factory_to_floor(int factory_index, int player_index, tile color);
		virtual int factory_to_lid(int factory_index, tile color);
		virtual int factory_to_center(int factory_index);
		bool handle_first_tile(int m_player_index);
	};
}
