#include "center_offer.h"

void control::center_offer::Execute()
{
	m_starter_tile = m_game->handle_center_starter_tile(m_player_index);
	m_tile_indices = m_game->get_center_tile_indices(m_color);
	m_moved_to_pattern_line = m_game->center_to_pattern_line(m_player_index, m_pattern_line_index, m_color);
	m_moved_to_floor = m_game->center_to_floor(m_player_index, m_color);
	m_moved_to_lid = m_game->center_to_lid(m_color);
}

void control::center_offer::Unexecute()
{
}
