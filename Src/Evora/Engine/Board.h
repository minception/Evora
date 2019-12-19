#pragma once

#include<array>

#include "Bag.h"
#include "Factory.h"
#include "Lid.h"
#include "Player.h"
#include "Tile.h"

namespace engine {
	class Board
	{
	private:
		static const int32_t MAX_PLAYERS = 4;
		static const int32_t MAX_FACTORIES = 9;
		Bag m_bag;
		Lid m_lid;
		std::array<Factory, MAX_FACTORIES> m_factories;
		std::array<Player, MAX_PLAYERS> m_players;
	};
}
