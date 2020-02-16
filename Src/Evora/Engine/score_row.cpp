#include "score_row.h"

using namespace control;

void score_row::Execute()
{
	m_score = m_game->score_wall_row(m_player_index, m_row);
}

void score_row::Unexecute()
{
}
