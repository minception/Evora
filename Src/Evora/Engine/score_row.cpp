#include "score_row.h"

using namespace control;

void score_row::execute(std::shared_ptr<model::game> game)
{
	m_score = game->score_wall_row(m_player_index, m_row);
}

void score_row::unexecute(std::shared_ptr<model::game> game)
{
	game->take_score(m_player_index, m_score);
}

std::unique_ptr<command> score_row::clone()
{
	return std::make_unique<score_row>(*this);
}

bool score_row::is_move()
{
	return false;
}

int score_row::player_index()
{
	return -1;
}
