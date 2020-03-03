#include "init_round.h"

void control::init_round::Execute(std::shared_ptr<model::game> game)
{
	game->shuffle_bag();
	game->starter_tile_unhandled();
	m_added_before_refill = game->bag_to_factories();
	if(m_added_before_refill < game->factory_count()*FACTORY_SIZE)
	{
		m_bag_refilled = true;
		m_lid_state = game->get_lid_state();
		game->refill_bag();
		game->shuffle_bag();
		m_added_after_refill = game->bag_to_factories();
	}
	else
	{
		m_bag_refilled = false;
		m_added_after_refill = 0;
	}
	
}

void control::init_round::Unexecute(std::shared_ptr<model::game> game)
{
	game->factories_to_bag();
}

std::unique_ptr<control::command> control::init_round::clone()
{
	return std::make_unique<init_round>(*this);
}
