#include "game.h"

namespace model
{
	game::game(int number_of_players)
	{
		const int number_of_factories = number_of_players * 2 + 1;
		for (int i = 0; i < number_of_factories; i++)
		{
			m_factories.emplace_back();
		}
		for (int i = 0; i < number_of_players; i++)
		{
			m_players.emplace_back();
		}
	}

	bool game::can_factory_offer(int player, int factory, tile color, int line)
	{
		int count = m_factories[factory].offer(color);
		if (count > 0 && m_players[player].can_put_color(line, color)) return true;
		return false;
	}

	bool game::can_center_offer(int player, tile color, int line)
	{
		int count = m_center.offer(color);
		if (count > 0 && m_players[player].can_put_color(line, color)) return true;
		return false;
	}

	int game::factory_count() const
	{
		return m_factories.size();
	}

	int game::player_count() const
	{
		return m_players.size();
	}

	void game::fill_factories()
	{
		for (auto && factory : m_factories)
		{
			if(!factory.fill(m_bag))
			{
				// refill the bag and if there aren't any tiles to refill the bag with in the lid, then stop filling the factories
				if (!m_bag.refill(m_lid)) break;
				factory.fill(m_bag);
			}
		}
	}

	void game::shuffle_bag()
	{
		m_bag.shuffle();
	}

	std::vector<factory>::const_iterator game::factories_begin() const
	{
		return m_factories.cbegin();
	}

	std::vector<factory>::const_iterator game::factories_end() const
	{
		return m_factories.cend();
	}

	std::vector<board>::const_iterator game::players_begin() const
	{
		return m_players.cbegin();
	}

	std::vector<board>::const_iterator game::players_end() const
	{
		return m_players.cend();
	}

	std::vector<tile>::const_iterator game::center_begin() const
	{
		return m_center.begin();
	}

	std::vector<tile>::const_iterator game::center_end() const
	{
		return m_center.end();
	}

	std::tuple<int, int> game::factory_to_pattern_line(int factory_index, int player_index,
		int pattern_line_index, tile color)
	{
		int count = m_factories[factory_index].pick_color(color);
		return m_players[player_index].add_tiles(pattern_line_index, count, color);
	}

	int game::add_to_floor(int player_index, int count, tile color)
	{
		return m_players[player_index].add_to_floor(count, color);
	}

	void game::add_to_lid(int count, tile color)
	{
		m_lid.add_tiles(count, color);
	}

	std::tuple<int, int, std::vector<int>> game::center_to_pattern_line(int player_index, int pattern_line_index, tile color)
	{
		auto [count, indices] = m_center.pick_color(color);
		auto [added_to_pattern_line, overflow] = m_players[player_index].add_tiles(pattern_line_index, count, color);
		return { added_to_pattern_line, overflow, indices };
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
