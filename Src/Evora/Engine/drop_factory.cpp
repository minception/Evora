#include "drop_factory.h"

using namespace control;

void drop_factory::Execute()
{
	m_first_to_center = m_game->handle_starter_tile(m_player_index);
	m_moved_to_floor = m_game->factory_to_floor(m_factory_index, m_player_index, m_color);
	m_moved_to_lid = m_game->factory_to_lid(m_factory_index, m_color);
	m_moved_to_center = m_game->factory_to_center(m_factory_index);
}

void drop_factory::Unexecute()
{
}
