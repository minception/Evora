﻿#include "center_offer.h"

using namespace control;

void center_offer::Execute(std::shared_ptr<model::game> game)
{
	m_starter_tile = game->handle_center_starter_tile(m_player_index);
	m_tile_indices = game->get_center_tile_indices(m_color);
	m_moved_to_pattern_line = game->center_to_pattern_line(m_player_index, m_pattern_line_index, m_color);
	m_moved_to_floor = game->center_to_floor(m_player_index, m_color);
	m_moved_to_lid = game->center_to_lid(m_color);
}

void center_offer::Unexecute(std::shared_ptr<model::game> game)
{
}

std::unique_ptr<command> center_offer::clone()
{
	return std::make_unique<center_offer>(*this);
}
