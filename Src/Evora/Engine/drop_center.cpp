#include "drop_center.h"

using namespace control;

void drop_center::Execute(std::shared_ptr<model::game> game)
{
	m_starter_tile = game->handle_center_starter_tile(m_player_index);
	m_tile_indices = game->get_center_tile_indices(m_color);
	m_moved_to_floor = game->center_to_floor(m_player_index, m_color);
	m_moved_to_lid = game->center_to_lid(m_color);
}

void drop_center::Unexecute(std::shared_ptr<model::game> game)
{
	game->floor_to_center(m_player_index, m_color, m_moved_to_floor, m_tile_indices);
	game->lid_to_center(m_color, m_moved_to_lid, m_tile_indices);
	if(m_starter_tile)
	{
		game->starter_tile_to_center(m_player_index);
	}
}

std::unique_ptr<command> drop_center::clone()
{
	return std::make_unique<drop_center>(*this);
}
