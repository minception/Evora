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

}
