#pragma once

#include "bag.h"
#include "board.h"
#include "center.h"
#include "factory.h"
#include "lid.h"
#include <memory>

namespace model
{
	/**
	 * \brief A class representing game model and containing current game state
	 */
	class game
	{
		bag m_bag;
		center m_center;
		std::vector<factory> m_factories;
		lid m_lid;
		std::vector<board> m_boards;
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

		virtual int bag_to_factories();
		
		virtual int factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color);
		virtual int factory_to_floor(int factory_index, int player_index, tile color);
		virtual int factory_to_lid(int factory_index, tile color);
		virtual int factory_to_center(int factory_index);

		virtual int center_to_pattern_line(int player_index, int pattern_line_index, tile color);
		virtual int center_to_floor(int player_index, tile color);
		virtual int center_to_lid(tile color);
		virtual bool handle_center_starter_tile(int player_index);
		std::vector<int> get_center_tile_indices(tile color);
		std::vector<int> get_score_indices(int player_index, int pattern_line_index, tile tile);
		
		virtual bool handle_starter_tile(int player_index);

		virtual tile tile_wall(int player_index, int pattern_line_index);
		virtual int score_wall_tile(int player_index, int pattern_line_index, tile tile);
		virtual int score_wall_color(int player_index, tile color);
		virtual int score_wall_line(int player_index, int line);
		virtual int score_wall_row(int player_index, int row);
		
		virtual int floor_to_lid(int player_index);
		virtual int score_floor(int player_index);
		int handle_floor_starter_tile(int player_index);

		virtual void starter_tile_unhandled();

		tile pattern_line_color(int player_index, int pattern_line_index);
		bool pattern_line_full(int player_index, int pattern_line_index);
		bool can_add_to_pattern_line(int player_index, int pattern_line_index, tile color);
		bool round_finished();
		void set_first_player(int player_index);
		int get_first_player();
		bool game_over();
		std::vector<model::tile> get_center_colors();
		std::vector<model::tile> get_factory_colors(int factory_index);
		int get_winner();
		
		int wall_line_count(int player_index, int line);
		int get_floor_score(int player_index);
		int get_pattern_line_score(int player_index, int pattern_line_index);
		void pattern_line_to_center(int player_index, int pattern_line_index, tile color, int count, std::vector<int>& is);
		void floor_to_center(int player_index, tile color, int count, std::vector<int>& is);
		void lid_to_center(tile color, int count, std::vector<int>& is);
		void starter_tile_to_center(int player_index);
		void floor_to_factory(int factory_index, int player_index, tile color, int count);
		void lid_to_factory(int factory_index, tile color, int count);
		void center_to_factory(int factory_index, int count);
		void remove_center_starter_tile();
		void pattern_line_to_factory(int factory_index, int player_index, int pattern_line_index, tile color, int count);
		void factories_to_bag();
		void take_score(int player_index, int score);
		void lid_to_floor(int player_index, int count);
		void add_starter_to_floor(int player_index, int position);
		void wall_to_pattern_line(int player_index, int pattern_line_index, tile tile);
	};
}
