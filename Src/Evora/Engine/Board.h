#pragma once

#include<vector>
#include<map>

#include "Bag.h"
#include "Factory.h"
#include "Lid.h"
#include "Player.h"
#include "Tile.h"
#include "Center.h"

namespace engine {
	using factories_iterator = std::vector<factory>::const_iterator;
	using players_iterator = std::vector<player>::const_iterator;
	class board
	{
	private:
		static const int32_t MAX_PLAYERS = 4;
		static const int32_t MAX_FACTORIES = 9;
		bag m_bag;
		lid m_lid;
		center m_center;
		std::vector<factory> m_factories;
		std::vector<player> m_players;
	public:
		board(int32_t players);
		void start_game();
		void fill_factories();
		void get_tiles_factory(size_t factory, type color);
		factories_iterator factories_begin() const;
		factories_iterator factories_end() const;
		players_iterator players_begin() const;
		players_iterator players_end() const;
		factory get_factory(size_t index);
		player get_player(size_t index);
	};
}
