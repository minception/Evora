#include "score_color.h"

using namespace control;

void score_color::Execute(std::shared_ptr<model::game> game)
{
	m_score = game->score_wall_color(m_player_index, m_color);
}

void score_color::Unexecute(std::shared_ptr<model::game> game)
{
}

std::unique_ptr<command> score_color::clone()
{
	return std::make_unique<score_color>(*this);

}
