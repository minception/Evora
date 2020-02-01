#include "factory_offer.h"

void control::factory_offer::Execute()
{
	m_first_to_center = m_game->handle_first_tile(m_player_index);
	m_moved_to_pattern_line = m_game->factory_to_pattern_line(m_factory_index, m_player_index, m_pattern_line_index, m_color);
	m_moved_to_floor = m_game->factory_to_floor(m_factory_index, m_player_index, m_color);
	m_moved_to_lid = m_game->factory_to_lid(m_factory_index, m_color);
	m_moved_to_center = m_game->factory_to_center(m_factory_index);
}

void control::factory_offer::Unexecute()
{
}
