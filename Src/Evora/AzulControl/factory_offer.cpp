#include "factory_offer.h"

void control::factory_offer::Execute()
{
	auto [moved_to_pattern_line, pattern_line_overflow] = m_game->factory_to_pattern_line(
		m_factory_index, m_player_index, m_pattern_line_index, m_color);
	m_moved_to_pattern_line = moved_to_pattern_line;
	if (pattern_line_overflow > 0)
	{
		m_moved_to_lid = m_game->add_to_floor(m_player_index, pattern_line_overflow, m_color);
		if (m_moved_to_lid > 0)
		{
			m_game->add_to_lid(m_moved_to_lid, m_color);
		}
		else m_moved_to_lid = 0;
	}
	else m_moved_to_floor = m_moved_to_lid = 0;
	//TODO: add starter tile handling
}

void control::factory_offer::Unexecute()
{
}
