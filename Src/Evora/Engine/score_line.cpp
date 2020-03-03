#include "score_line.h"

using namespace control;

void score_line::Execute(std::shared_ptr<model::game> game)
{
	m_score = game->score_wall_line(m_player_index, m_line);
}

void score_line::Unexecute(std::shared_ptr<model::game> game)
{
	game->take_score(m_player_index, m_score);
}

std::unique_ptr<command> score_line::clone()
{
	return std::make_unique<score_line>(*this);
}
