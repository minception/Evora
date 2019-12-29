#include "Board.h"

namespace engine {
	board::board(int32_t players)
	{
		int numberOfFactories = players * 2 + 1;
		for (size_t i = 0; i < numberOfFactories; i++)
		{
			m_factories[i] = factory();
		}
	}

	void board::start_game()
	{
		m_bag.generateTiles();
		m_bag.shuffle();
	}
}
