#include "score_color.h"

using namespace control;

void score_color::Execute()
{
	m_score = m_game->score_wall_color(m_player_index, m_color);
}

void score_color::Unexecute()
{
}
