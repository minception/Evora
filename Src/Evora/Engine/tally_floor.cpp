#include "tally_floor.h"

void control::tally_floor::Execute()
{
	m_score = m_game->score_floor(m_player_index);
	m_starter_tile_position = m_game->handle_floor_starter_tile(m_player_index);
	m_floor_size = m_game->floor_to_lid(m_player_index);
}

void control::tally_floor::Unexecute()
{
}
