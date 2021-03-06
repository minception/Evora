#include "init_round.h"

void control::init_round::execute(std::shared_ptr<model::game> game)
{
	game->shuffle_bag();
	game->set_starter_tile_handled(false);
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

void control::init_round::unexecute(std::shared_ptr<model::game> game)
{
	game->factories_to_bag();
	if(m_bag_refilled)
	{
		for(auto&& lid_tile: m_lid_state)
		{
			game->remove_tile_from_bag(lid_tile);
		}
		game->set_lid_state(m_lid_state);
	}
	game->set_starter_tile_handled(true);
}

std::unique_ptr<control::command> control::init_round::clone()
{
	return std::make_unique<init_round>(*this);
}

bool control::init_round::is_move()
{
	return false;
}

int control::init_round::player_index()
{
	return -1;
}
