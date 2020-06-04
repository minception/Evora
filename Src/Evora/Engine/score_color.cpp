#include "score_color.h"

using namespace control;

void score_color::execute(std::shared_ptr<model::game> game)
{
	m_score = game->score_wall_color(m_player_index, m_color);
}

void score_color::unexecute(std::shared_ptr<model::game> game)
{
	game->take_score(m_player_index, m_score);
}

std::unique_ptr<command> score_color::clone()
{
	return std::make_unique<score_color>(*this);
}

bool score_color::is_move()
{
	return false;
}

int score_color::player_index()
{
	return -1;
}
