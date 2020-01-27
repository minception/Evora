#include "center_offer.h"

void control::center_offer::Execute()
{
	auto [moved_to_pattern_line, pattern_line_overflow, indices] = m_game->center_to_pattern_line(
		m_player_index, m_pattern_line_index, m_color);
	m_moved_to_pattern_line = moved_to_pattern_line;
	int floor_overflow = m_game->add_to_floor(m_player_index, pattern_line_overflow, m_color);
	m_game->add_to_lid(floor_overflow, m_color);
	//TODO: add first player handling
}

void control::center_offer::Unexecute()
{
}
