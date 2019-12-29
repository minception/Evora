#include "Board.h"

namespace engine {
	board::board(int32_t players)
	{
		const size_t numberOfFactories = players * 2 + 1;
		for (size_t i = 0; i < numberOfFactories; i++)
		{
			m_factories[i] = factory();
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
}
