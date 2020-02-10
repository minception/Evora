#include "score_wall_tile.h"

using namespace control;

void control::score_wall_tile::Execute()
{
	m_score = m_game->score_wall_tile(m_player_index, m_line, m_color);
}

void score_wall_tile::Unexecute()
{
}
