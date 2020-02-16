#include "score_line.h"

using namespace control;

void score_line::Execute()
{
	m_score = m_game->score_wall_line(m_player_index, m_line);
}

void score_line::Unexecute()
{
}
