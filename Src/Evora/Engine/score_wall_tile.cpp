#include "score_wall_tile.h"

using namespace control;

void control::score_wall_tile::Execute(std::shared_ptr<model::game> game)
{
	m_score = game->score_wall_tile(m_player_index, m_line, m_color);
}

void score_wall_tile::Unexecute(std::shared_ptr<model::game> game)
{
}

std::unique_ptr<command> score_wall_tile::clone()
{
	return std::make_unique<score_wall_tile>(*this);
}
