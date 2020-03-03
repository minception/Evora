#include "tally_floor.h"

using namespace control;

void tally_floor::Execute(std::shared_ptr<model::game> game)
{
	m_score = game->score_floor(m_player_index);
	m_starter_tile_position = game->handle_floor_starter_tile(m_player_index);
	m_floor_size = game->floor_to_lid(m_player_index);
}

void tally_floor::Unexecute(std::shared_ptr<model::game> game)
{
	game->lid_to_floor(m_player_index, m_floor_size);
	if(m_starter_tile_position != -1)
	{
		game->add_starter_to_floor(m_player_index, m_starter_tile_position);
	}
	game->take_score(m_player_index, m_score);
}

std::unique_ptr<command> tally_floor::clone()
{
	return std::make_unique<tally_floor>(*this);
}
