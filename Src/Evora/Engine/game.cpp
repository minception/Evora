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

	int game::factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color)
	{
		int res(0);
		while(!m_boards[player_index].pattern_line_full(pattern_line_index))
		{
			if (m_factories[factory_index].pick_color_tile(color))
			{
				m_boards[player_index].add_to_pattern_line(pattern_line_index, color);
				++res;
			}
			else break;
		}
		return res;
	}

	int game::factory_to_floor(int factory_index, int player_index, tile color)
	{
		int res(0);
		while (!m_boards[player_index].floor_full())
		{
			if (m_factories[factory_index].pick_color_tile(color))
			{
				m_boards[player_index].add_to_floor(color);
				++res;
			}
			else break;
		}
		return res;
	}

	int game::factory_to_lid(int factory_index, tile color)
	{
		int res(0);
		while (m_factories[factory_index].pick_color_tile(color))
		{
			m_lid.add_tile(color);
			++res;
		}
		return res;
	}

	int game::factory_to_center(int factory_index)
	{
		return m_factories[factory_index].add_to_center(m_center);
	}

	bool game::handle_first_tile(int m_player_index)
	{
		if(m_starter_tile_handled)
		{
			return false;
		}
		m_center.add_tile(tile::starter);
		return true;
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
