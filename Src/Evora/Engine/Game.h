#pragma once
#include "Board.h"

namespace engine
{
	class Game
	{
	private:
		board m_board;
	public:
		Game(int numberOfPlayers);
	};
}

