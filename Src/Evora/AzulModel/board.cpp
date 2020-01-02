#include "board.h"

model::board::board(int number_of_players)
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
