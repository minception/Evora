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

	bool game::center_offer(int player, tile color, int line)
	{
		bool starter;
		int count = m_center.offer(color, starter);
		if (count == 0) return false;
		if(m_players[player].add_tiles(line, count, color, m_lid, starter))
		{
			m_center.pick_color(color);
			return true;
		}
		return false;
	}

	bool game::tile_walls()
	{
		bool res = false;
		for (auto && player : m_players)
		{
			if(player.tile_wall(m_lid)) res = true;
		}
		return res;
	}

	int game::get_winner()
	{
		int max_score = 0;
		int winner = 0;
		for (int i = 0; i < m_players.size(); i++)
		{
			if (m_players[i].get_score() > max_score) winner = i;
		}
		return winner;
	}

	bool game::factories_empty()
	{
		for (auto && factory : m_factories)
		{
			if (!factory.empty()) return false;
		}
		return true;
	}

	bool game::center_empty() const
	{
		return m_center.empty();
	}
}
