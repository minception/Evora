#include "init_round.h"

void control::init_round::Execute()
{
	m_game->shuffle_bag();
	m_game->starter_tile_unhandled();
	m_added_before_refill = m_game->bag_to_factories();
	if(m_added_before_refill < m_game->factory_count()*FACTORY_SIZE)
	{
		m_bag_refilled = true;
		m_lid_state = m_game->get_lid_state();
		m_game->refill_bag();
		m_game->shuffle_bag();
		m_added_after_refill = m_game->bag_to_factories();
	}
	else
	{
		m_bag_refilled = false;
		m_added_after_refill = 0;
	}
	
}

void control::init_round::Unexecute()
{
	
}
