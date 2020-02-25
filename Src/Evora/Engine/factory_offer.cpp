#include "factory_offer.h"

using namespace control;

void factory_offer::Execute(std::shared_ptr<model::game> game)
{
	m_first_to_center = game->handle_starter_tile(m_player_index);
	m_moved_to_pattern_line = game->factory_to_pattern_line(m_factory_index, m_player_index, m_pattern_line_index, m_color);
	m_moved_to_floor = game->factory_to_floor(m_factory_index, m_player_index, m_color);
	m_moved_to_lid = game->factory_to_lid(m_factory_index, m_color);
	m_moved_to_center = game->factory_to_center(m_factory_index);
}

void factory_offer::Unexecute(std::shared_ptr<model::game> game)
{
}

std::unique_ptr<command> factory_offer::clone()
{
	return std::make_unique<factory_offer>(*this);
}
