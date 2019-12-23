#include "Board.h"
namespace engine {
	Board::Board(int32_t players)
	{
		int numberOfFactories = players * 2 + 1;
		for (size_t i = 0; i < numberOfFactories; i++)
		{
			m_factories[i] = Factory();
		}
	}
	Board::~Board() {}
}
