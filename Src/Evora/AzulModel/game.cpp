#include "game.h"

namespace model
{
	game::game(int number_of_players)
	{
		int number_of_factories = number_of_players * 2 + 1;
		for (int i = 0; i < number_of_factories; i++)
		{
			m_factories.emplace_back();
		}
		for (int i = 0; i < number_of_players; i++)
		{
			m_players.emplace_back();
		}
	}

	bool game::factory_offer(int player, int factory, tile color, int line)
	{
		int count = m_factories[factory].offer(color);
		if (count == 0) return false;
		if(m_players[player].add_tiles(line, count, color, m_lid))
		{
			m_factories[factory].pick_color(color, m_center);
			return true;
		}
		return false;
	}
}
