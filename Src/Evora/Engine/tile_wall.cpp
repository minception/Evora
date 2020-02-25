﻿#include "tile_wall.h"

void control::tile_wall::Execute(std::shared_ptr<model::game> game)
{
	m_color = game->tile_wall(m_player_index, m_pattern_line_index);
}

void control::tile_wall::Unexecute(std::shared_ptr<model::game> game)
{
}

std::unique_ptr<control::command> control::tile_wall::clone()
{
	return std::make_unique<tile_wall>(*this);
}
