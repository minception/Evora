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
			m_boards.emplace_back();
		}
		m_starter_tile_handled = false;
	}

	int game::factory_count()
	{
		return m_factories.size();
	}

	int game::player_count()
	{
		return m_boards.size();
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
		return m_boards.cbegin();
	}

	std::vector<board>::const_iterator game::players_end() const
	{
		return m_boards.cend();
	}

	std::vector<tile>::const_iterator game::center_begin() const
	{
		return m_center.begin();
	}

	std::vector<tile>::const_iterator game::center_end() const
	{
		return m_center.end();
	}

	void game::shuffle_bag()
	{
		m_bag.shuffle();
	}

	int game::bag_to_factories()
	{
		int res = 0;
		for (auto && factory : m_factories)
		{
			res += factory.fill(m_bag);
			if (m_bag.empty()) return res;
		}
		return res;
	}

	std::vector<tile> game::get_lid_state()
	{
		return m_lid.get_state();
	}

	void game::refill_bag()
	{
		m_bag.refill(m_lid); 
	}
}
