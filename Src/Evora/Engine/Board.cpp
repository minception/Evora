#include "Board.h"

namespace engine {
	board::board(int32_t players)
	{
		const size_t numberOfFactories = 2 * players + 1;
		for (size_t i = 0; i < numberOfFactories; i++)
		{
			m_factories.emplace_back();
		}
	}

	void board::start_game()
	{
		m_bag.generateTiles();
		m_bag.shuffle();
		fill_factories();
	}

	void board::fill_factories()
	{
		for (auto&& factory : m_factories)
		{
			if(!factory.fill(m_bag))
			{
				if(!m_bag.refill(m_lid))
				{
					// rare occasion when both bag and lid are empty
					return;
				}
				// finish filling the factory
				factory.fill(m_bag);
			}
		}
	}

	void board::get_tiles_factory(size_t factory, type color)
	{
		_ASSERT(factory <= m_factories.size(), "trying to access nonexistent factory");
		
	}

	factories_iterator board::factories_begin() const
	{
		return m_factories.cbegin();
	}

	factories_iterator board::factories_end() const
	{
		return  m_factories.cend();
	}

	players_iterator board::players_begin() const
	{
		return m_players.cbegin();
	}

	players_iterator board::players_end() const
	{
		return m_players.cend();
	}
}
