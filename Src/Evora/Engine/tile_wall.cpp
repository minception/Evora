#include "tile_wall.h"

void control::tile_wall::execute(std::shared_ptr<model::game> game)
{
	m_color = game->tile_wall(m_player_index, m_pattern_line_index);
}

void control::tile_wall::unexecute(std::shared_ptr<model::game> game)
{
	game->wall_to_pattern_line(m_player_index, m_pattern_line_index, m_color);
}

std::unique_ptr<control::command> control::tile_wall::clone()
{
	return std::make_unique<tile_wall>(*this);
}

bool control::tile_wall::is_move()
{
	return false;
}

int control::tile_wall::player_index()
{
	return -1;
}
